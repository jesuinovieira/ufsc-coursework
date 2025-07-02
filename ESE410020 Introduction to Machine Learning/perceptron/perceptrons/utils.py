import numpy as np


def shuffle(X, y):
    # Randomly shuffle two arrays in the same order.
    mask = np.random.permutation(len(X))
    return X[mask], y[mask]
