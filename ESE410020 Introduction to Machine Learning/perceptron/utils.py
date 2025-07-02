import logging
import os
import sys

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


def split(X, y, trainsize=0.7, path=None):
    # Split dataset for training and test purpose
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, train_size=trainsize, shuffle=True, stratify=y
    )

    if path:
        if not os.path.isdir(path):
            os.makedirs(path)

        np.save(f"{path}/X_train.npy", X_train)
        np.save(f"{path}/y_train.npy", y_train)

        np.save(f"{path}/X_test.npy", X_test)
        np.save(f"{path}/y_test.npy", y_test)

    return X_train, X_test, y_train, y_test
