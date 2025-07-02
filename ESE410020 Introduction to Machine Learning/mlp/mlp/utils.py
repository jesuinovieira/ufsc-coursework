import numpy as np


def shuffle(X, y):
    # Randomly shuffle two arrays in the same order.
    mask = np.random.permutation(len(X))
    return X[mask], y[mask]


def onehot(data):
    data = np.hstack(data)
    shape = (data.size, data.max() + 1)
    rows = np.arange(data.size)

    new = np.zeros(shape)
    new[rows, data] = 1

    return new


def elapsed(delta):
    if delta > 86400:
        return f"{round(delta / 86400, 4)} days"
    if delta > 3600:
        return f"{round(delta / 3600, 4)} hours"
    if delta > 60:
        return f"{round(delta / 60, 4)} minutes"

    return f"{round(delta, 4)} seconds"
