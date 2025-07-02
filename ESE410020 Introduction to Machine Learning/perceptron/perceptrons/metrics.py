import numpy as np


def get(fname):
    if fname == "mse":
        return mse
    if fname == "acc":
        return acc

    raise AssertionError(f"Invalid metric '{fname}'")


def mse(verror):
    # Mean squared error
    squared = np.square(verror)
    return np.sum(squared) / len(verror)


def acc(verror):
    # Accuracy
    return np.count_nonzero(verror == 0) / len(verror)
