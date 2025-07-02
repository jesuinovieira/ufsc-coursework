import shutil

import numpy as np

import mlp
import utils


logger = utils.getlogger(__name__)


def buildmodel(inputsize, outputsize, neurons, eta, alpha):
    model = mlp.MLP()

    model.add(mlp.layers.Input(inputsize, name="Input"))  # Not a layer

    for i, neuron in enumerate(neurons):
        model.add(
            mlp.layers.Dense(
                neuron, eta=eta, alpha=alpha, activation="tanh", name=f"Hidden-{i + 1}"
            )
        )

    model.add(
        mlp.layers.Dense(
            outputsize, eta=eta, alpha=alpha, activation="tanh", name="Output"
        )
    )

    return model


def main():
    X_train, X_test, y_train, y_test = utils.loadmnist("data")
    inputsize = X_train.shape[1]
    outputsize = len(np.unique(y_train))

    modelscfg = utils.loadconfig("config.json")

    nofc = 0
    for item in modelscfg:
        nofc += 1
        neurons, eta, alpha, epochs = item

        model = buildmodel(inputsize, outputsize, neurons, eta, alpha)
        model.compile(loss="mse", path="checkpoints")
        model.fit(X_train, y_train, epochs=epochs)
        loss, acc = model.evaluate(X_test, y_test)

        utils.saveresults(*item, loss, acc, model.path)

        logger.info("")
        logger.info(f"Test loss: {round(loss, 4)}")
        logger.info(f"Test accuracy: {round(acc, 4)}\n")
        model.summary()
        logger.info(
            f"neurons/layer: {neurons}\n"
            f"eta: {eta}\n"
            f"alpha: {alpha}\n"
            f"epochs: {epochs}\n\n"
        )

    logger.info(f"Number of combinations: {nofc}")

    original = r"output.log"
    target = r"checkpoints/output.log"
    shutil.copyfile(original, target)


if __name__ == "__main__":
    main()
