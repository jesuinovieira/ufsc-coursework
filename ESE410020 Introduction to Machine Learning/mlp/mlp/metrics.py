import numpy as np


def get(fname):
    if fname == "mse":
        return mse
    if fname == "er":
        return er
    if fname == "acc":
        return acc

    raise AssertionError(f"Invalid metric '{fname}'")


def mse(verror):
    squared = np.square(verror)
    return np.sum(squared) / len(verror)


def er(verror):
    squared = np.square(verror)
    return np.sum(squared) / (2 * len(verror))


def acc(iscorrect):
    return np.sum(iscorrect) / len(iscorrect)


# def crossentropy(p, q):
#     pass
