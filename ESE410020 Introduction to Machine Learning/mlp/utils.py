import itertools
import json

import logging
import os
import sys

import mlxtend.data
import numpy as np
from sklearn.model_selection import train_test_split


def getlogger(name, logfile="output.log"):
    for handler in logging.root.handlers[:]:
        logging.root.removeHandler(handler)

    fhandler = logging.FileHandler(logfile)
    shandler = logging.StreamHandler(sys.stdout)

    formatter = logging.Formatter("%(asctime)s %(levelname)s %(name)s: %(message)s")
    fhandler.setFormatter(formatter)
    formatter = logging.Formatter("%(message)s")
    shandler.setFormatter(formatter)

    params = {"level": logging.DEBUG, "handlers": [fhandler, shandler]}
    logging.basicConfig(**params)

    fhandler.setLevel(logging.DEBUG)
    shandler.setLevel(logging.DEBUG)

    logging.getLogger("matplotlib").setLevel(logging.WARNING)
    logging.getLogger("matplotlib.legend").setLevel(logging.WARNING)
    logging.getLogger("matplotlib.font_manager").setLevel(logging.WARNING)
    logging.getLogger("matplotlib.backends.backend_pdf").setLevel(logging.WARNING)

    return logging.getLogger(name)


def loadconfig(filepath):
    with open(filepath) as f:
        data = json.load(f)

    combinations = itertools.product(
        data["neurons"], data["eta"], data["alpha"], data["epochs"]
    )

    return combinations


def saveresults(neurons, eta, alpha, epochs, testloss, testacc, path):
    results = {
        "neurons": neurons,
        "eta": eta,
        "alpha": alpha,
        "epochs": epochs,
        "testacc": testacc,
        "testloss": testloss,
    }

    with open(f"{path}/results.json", "w") as fp:
        json.dump(results, fp, indent=4)


def loadmnist(path):
    X_train = np.load(f"{path}/X_train.npy")
    X_test = np.load(f"{path}/X_test.npy")
    y_train = np.load(f"{path}/y_train.npy")
    y_test = np.load(f"{path}/y_test.npy")

    return X_train, X_test, y_train, y_test


def splitmnist(trainsize, testsize):
    X_train, y_train = mlxtend.data.loadlocal_mnist(
        images_path="rawdata/train-images-idx3-ubyte",
        labels_path="rawdata/train-labels-idx1-ubyte",
    )

    X_test, y_test = mlxtend.data.loadlocal_mnist(
        images_path="rawdata/t10k-images-idx3-ubyte",
        labels_path="rawdata/t10k-labels-idx1-ubyte",
    )

    X_train = X_train / 255.0
    y_train = y_train.reshape(-1, 1)

    X_test = X_test / 255.0
    y_test = y_test.reshape(-1, 1)

    X_train, _, y_train, _ = split(X_train, y_train, trainsize)
    X_test, _, y_test, _ = split(X_test, y_test, testsize)

    # import matplotlib.pyplot as plt
    # for i in range(9):
    #     plt.subplot(330 + 1 + i)
    #     sample = X[i].reshape(28, 28, 1)
    #     plt.imshow(sample, cmap=plt.get_cmap("gray"))
    # plt.show()

    return X_train, X_test, y_train, y_test


def split(X, y, trainsize=0.7):
    # Split dataset for training and test purpose
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, train_size=trainsize, shuffle=True, stratify=y
    )

    return X_train, X_test, y_train, y_test


if __name__ == "__main__":
    X_train, X_test, y_train, y_test = splitmnist(
        trainsize=2000/60000, testsize=1000/10000
    )

    path = "data"
    if not os.path.isdir(path):
        os.makedirs(path)

    np.save(f"{path}/X_train.npy", X_train)
    np.save(f"{path}/y_train.npy", y_train)

    np.save(f"{path}/X_test.npy", X_test)
    np.save(f"{path}/y_test.npy", y_test)

    # print(f"Number of objecter per class for the training set")
    # for i in range(10):
    #     mask = y_train[:, 0] == i
    #     qtd = len(y_train[mask])
    #     print(f"Class {i}: {qtd}")
    #
    # print(f"\nNumber of objecter per class for the training set")
    # for i in range(10):
    #     mask = y_test[:, 0] == i
    #     qtd = len(y_test[mask])
    #     print(f"Class {i}: {qtd}")
