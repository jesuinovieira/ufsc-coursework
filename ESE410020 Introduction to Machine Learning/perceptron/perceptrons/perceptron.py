import logging
import os
import pickle
import time

import numpy as np
import randomname

from . import activations
from . import metrics
from . import utils


class Perceptron:
    def __init__(self, name=randomname.get_name()):
        self.name = name
        self.threshold = 0
        self.activation = activations.get("sgn")
        self.history = {"loss": [], "acc": [], "eta": None, "a": [], "b": []}

        self.w = None
        self.eta = None
        self.tol = None
        self.loss = None
        self.path = None

        self._logger = logging.getLogger(type(self).__name__)

    def compile(self, eta=10e-1, loss="mse", tol=1e-2, path=None):
        # Configures the model for training
        assert 0 < eta <= 1, (
            "The learning-rate parameter is a positive constant "
            "limited to the range 0 < eta <= 1"
        )

        self.eta = eta
        self.history["eta"] = self.eta
        self.loss = metrics.get(loss)
        self.tol = tol

        if path:
            now = time.time()
            timestamp = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime(now))
            path = os.path.join(path, timestamp)
            if not os.path.isdir(path):
                os.makedirs(path)
            self.path = path

    def fit(self, X, y_true, epochs):
        C = np.unique(y_true)
        assert len(C) == 2, f"Only binary problems are accepted, {len(C)} classes found"

        # Initialize weights randomly, including bias
        m = X.shape[1] + 1
        self.w = np.random.uniform(low=0, high=1, size=m)

        # Save first decision boundary (from random weights) too
        self._savedb()

        s1 = time.time()
        for epoch in range(epochs):
            self._logger.info(f"Epoch {epoch + 1}/{epochs}")
            s2 = time.time()
            verror = np.array([])

            # Shuffle data for each epoch
            X, y_true = utils.shuffle(X, y_true)
            for x, d in zip(X, y_true):
                y_pred = self.predict(x)
                error = d - y_pred
                verror = np.append(verror, error)

                # Add fixed bias input (+1)
                x = np.insert(x, 0, 1, axis=0)
                # Update weights using on-line method: adjustments to the synaptic
                # weights are performed on an example-by-example basis. The cost
                # function to be minimized is the total instantaneous error energy
                self.w = self.w + self.eta * error * x

            # Save current state and print out some infos
            loss = metrics.mse(verror)
            acc = metrics.acc(verror)

            self.history["loss"].append(loss)
            self.history["acc"].append(acc)
            self._savedb()

            if self.path:
                file = f"{self.path}/E{epoch}-L{round(loss, 4)}.pickle"
                self.save(file)

            e2 = time.time()
            elapsed = e2 - s2

            self._logger.info(
                f"{len(X)}/{len(X)} [==============================] "
                f"{round(elapsed, 0)}s "
                f"- loss: {round(self.history['loss'][-1], 4)} "
                f"- acc: {round(self.history['acc'][-1], 4)}"
            )

            # Stop condition
            if self.history["loss"][-1] <= self.tol:
                break

        e1 = time.time()
        elapsed = e1 - s1
        self._logger.info(f"")
        self._logger.info(f"Elapsed time: {round(elapsed, 4)}s")

    def predict(self, X):
        # Add fixed bias input (+1)
        X = np.insert(X, 0, 1, axis=1 if X.ndim > 1 else 0)
        # Calculate induced local field
        v = self.w @ X.T
        # Apply the activation function in the induced local field, i.e., neuron output
        y = np.vectorize(self.activation)(v)

        return y

    def evaluate(self, X, y_true):
        y_pred = self.predict(X)
        verror = y_true - y_pred

        return metrics.acc(verror), metrics.mse(verror)

    def save(self, filename=None):
        if not filename:
            filename = self.name

        with open(filename, "wb") as f:
            pickle.dump(self, f)

    @staticmethod
    def load(filename):
        with open(filename, "rb") as f:
            model = pickle.load(f)
        return model

    def _savedb(self):
        # Decision boundary:
        #   w0 * x0 + w1 * x1 + w2 * x2 = 0
        # Where x0 = 1, and w0 = b
        # Let x1 = x and x2 = y. The equation can then be rewritten:
        #   y = - (w1 * x + b) / w2
        #   y = a * x + b
        # Where a = - w1 / w2 and b = - b / w2
        self.history["a"].append(-self.w[1] / self.w[2])
        self.history["b"].append(-self.w[0] / self.w[2])
