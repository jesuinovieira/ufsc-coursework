import numpy as np

import generator
import perceptron
import plot
import utils


logger = utils.getlogger(__name__)


def E1():
    etas = np.linspace(1e-5, 1e-0, 5)

    # Create a linearly separable dataset
    X, y = generator.moons(na=1500, nb=1500, d=0.5, r=10, w=6)
    X_train, X_test, y_train, y_test = utils.split(X, y, trainsize=1/3, path="data/E1")

    models = []
    for eta in etas:
        model = perceptron.Perceptron()
        model.compile(eta=eta, loss="mse", tol=0.0, path=f"checkpoints/E1/ETA{eta:4e}")
        model.fit(X_train, y_train, epochs=50)
        acc, loss = model.evaluate(X_test, y_test)

        # logger.info(f"Eta: {eta:.4e}")
        logger.info(f"Test loss: {loss}")
        logger.info(f"Test accuracy: {acc}\n")

        models.append(model)

    plot.results(models, X_test, y_test, "output", "e1")


def E2():
    # Create a non linearly separable dataset
    X, y = generator.moons(na=1500, nb=1500, d=-4, r=10, w=6)
    X_train, X_test, y_train, y_test = utils.split(X, y, trainsize=1/3, path="data/E2")

    eta = 1e-5

    model = perceptron.Perceptron()
    model.compile(eta=eta, loss="mse", tol=0.0, path="checkpoints/E2")
    model.fit(X_train, y_train, epochs=50)
    acc, loss = model.evaluate(X_test, y_test)

    logger.info(f"Test loss: {loss}")
    logger.info(f"Test accuracy: {acc}\n")

    plot.results([model], X_test, y_test, "output", "e2")


if __name__ == "__main__":
    E1()
    E2()
