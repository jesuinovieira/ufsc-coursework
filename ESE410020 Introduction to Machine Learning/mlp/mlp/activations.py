import numpy as np


def get(fname):
    if fname == "sigmoid":
        return sigmoid, dsigmoid
    if fname == "tanh":
        return tanh, dtanh
    if fname == "relu":
        return relu, drelu
    if fname == "softmax":
        return softmax, dsoftmax

    raise AssertionError(f"Invalid activation function '{fname}'")


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))


def dsigmoid(x):
    outcome = sigmoid(x)
    return outcome * (1 - outcome)


def tanh(x):
    return np.tanh(x)


def dtanh(x):
    return 1.0 - np.tanh(x) ** 2


def relu(x):
    return np.maximum(0, x)


def drelu(x):
    return 1.0 * (x > 0)


# def leakyrelu(x):
#     return np.maximum(leaky_slope * x, x)
#
#
# def dleakyrelu(x):
#     d = np.zeros_like(x)
#     d[x <= 0] = leaky_slope
#     d[x > 0] = 1
#     return d


def softmax(x):
    """Compute the softmax of vector x in a numerically stable way."""
    shiftx = x - np.max(x)
    exps = np.exp(shiftx)
    return exps / np.sum(exps)


def dsoftmax(s):
    # https://towardsdatascience.com/derivative-of-the-softmax-function-and-the-categorical-cross-entropy-loss-ffceefc081d1
    # https://stats.stackexchange.com/questions/79454/softmax-layer-in-a-neural-network
    # Reshape the 1-d softmax to 2-d so that np.dot will do the matrix multiplication
    s = s.reshape(-1, 1)
    return np.diagflat(s) - np.dot(s, s.T)
