import logging
import os.path
import pickle
import time

import numpy as np
import randomname

from . import metrics
from . import utils


class MLP:
    def __init__(self, layers=None, name=randomname.get_name()):
        # MLP for classification tasks
        # Classes are predicted from 0 -> n - 1, where n is the number of classes
        self.layers = []
        self.name = name

        self.loss = None
        self.tol = None
        self.path = None
        self.history = {"loss": [], "acc": []}

        if layers:
            for layer in layers:
                self.add(layer)

        self._logger = logging.getLogger(type(self).__name__)

    def add(self, layer):
        # Assume that the user has already specified the shape of the input layer.
        # Therefore, we define it only for hidden and output layers
        if self.layers:
            # The input of the current last layer is the output of the previous one
            layer.inputs = self.layers[-1].units
            self.layers[-1].last = False

        self.layers.append(layer)
        self.layers[-1].last = True

    def compile(self, loss="mse", tol=1e-2, path=None):
        # Configures the model for training
        self.tol = tol
        self.loss = metrics.get(loss)

        if path:
            now = time.time()
            timestamp = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime(now))
            path = os.path.join(path, timestamp)
            if not os.path.isdir(path):
                os.makedirs(path)
            self.path = path

    def fit(self, X, y_true, epochs):
        # Train our network on a given batch of X and y_true. We first need to run
        # forward to get all layer activations. Then we can run backward going
        # from last to first layer. After we have called backward for all layers, all
        # Dense layers have already made one gradient step.
        s1 = time.time()
        y_true = utils.onehot(y_true)

        for epoch in range(epochs):
            self._logger.info(f"Epoch {epoch + 1}/{epochs}")
            s2 = time.time()

            verror = np.array([])
            iscorrect = np.array([])

            # Shuffle data for each epoch
            X, y_true = utils.shuffle(X, y_true)
            for x, d in zip(X, y_true):
                y_pred = self.forward(x)
                error = d - y_pred
                self.backward(error)

                verror = np.append(verror, error)
                iscorrect = np.append(iscorrect, np.argmax(d) == np.argmax(y_pred))

            loss = self.loss(verror)
            acc = metrics.acc(iscorrect)

            self.history["loss"].append(loss)
            self.history["acc"].append(acc)

            if self.path:
                file = f"{self.path}/E{epoch + 1}-L{round(loss, 4)}.pickle"
                self.save(file)

            e2 = time.time()
            delta = e2 - s2

            self._logger.info(
                f"{len(X)}/{len(X)} [==============================] "
                f"{utils.elapsed(delta)} "
                f"- loss: {round(self.history['loss'][-1], 4)} "
                f"- acc: {round(self.history['acc'][-1], 4)} "
            )

            # Stop condition
            if self.history["loss"][-1] <= self.tol:
                break

        e1 = time.time()
        delta = e1 - s1
        self._logger.info(f"")
        self._logger.info(f"Elapsed time: {utils.elapsed(delta)}")

    def forward(self, x):
        # Calculate an output from a neural network by propagating an input signal
        # through each layer until the output layer outputs its values

        # For the first iteration, x is the input vector
        for layer in self.layers:
            if not layer.trainable:
                continue

            output = layer.forward(x)

            # For other iterations, the outputs of the previous layer become the inputs
            # to the neurons on the next
            x = output

        # Returns the outputs from the output layer (note that x is the output of the
        # last layer)
        y_pred = x
        return y_pred

    def backward(self, error):
        # The backward starts at the output layer by passing the error signals leftward
        # through the network, layer by layer, and recursively computing the the local
        # gradient $\Delta$ for each neuron
        for layer in reversed(self.layers):
            if not layer.trainable:
                continue
            error = layer.backward(error)

    def predict(self, X, argmax=False):
        # Compute network predictions
        # If argmax=True, return a list of list (output values of the neurons)
        # If argmax=False, return a list (predicted class for each sample)
        y_pred = np.array(list(map(self.forward, X)))
        # y_pred = np.vectorize(self.forward)(self, X)

        if argmax:
            y_pred = y_pred.argmax(axis=1)

        return y_pred

    def evaluate(self, X, y_true):
        y_pred = self.predict(X)

        y_true = utils.onehot(y_true)

        verror = (y_true - y_pred).flatten()
        vacc = np.argmax(y_true, axis=1) == np.argmax(y_pred, axis=1)

        return self.loss(verror), metrics.acc(vacc)

    def summary(self):
        self._logger.info(
            f"Model: {self.name}\n"
            f"======================================================================\n"
            f"{'Layer <type>':<31} {'Input':<31} {'Params'}\n"
            f"----------------------------------------------------------------------"
        )

        total = []
        if self.layers:
            for layer in self.layers:
                first = f"{layer.name} ({layer.__class__.__name__})"
                if hasattr(layer, "w"):
                    # Sum one bias for each unit
                    params = layer.inputs * layer.units + layer.units
                    total.append(params)
                else:
                    params = 0
                self._logger.info(f"{first:<31} {layer.units:<31} {params}")

        self._logger.info(
            f"======================================================================\n"
            f"Total params: {sum(total)}"
        )

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
