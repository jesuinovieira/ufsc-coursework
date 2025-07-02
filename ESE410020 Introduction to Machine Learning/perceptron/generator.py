import numpy as np


def moons(na=1500, nb=1500, d=6, r=10, w=6):
    """Make two interleaving half circles. Described in Section 1.5, Haykin, S., Neural
    Networks and Learning Machines, 3d Edition, 2008.

    :param na: number of data points in Region A
    :param nb: number of data points in Region B
    :param d: distance separating the two moons
    :param r: radius of each moon
    :param w: width of each moon
    :return: ndarray of shape (na + nb, 2) with the generated samples and ndarray of
    shape (na + nb,) with the integer labels (0 or 1) for class membership of each
    sample
    """
    xa = r * np.cos(np.linspace(0, np.pi, na))
    ya = r * np.sin(np.linspace(0, np.pi, na))
    xb = r * np.cos(np.linspace(0, np.pi, nb)) + r
    yb = -1 * r * np.sin(np.linspace(0, np.pi, nb)) - d

    X = np.vstack([np.append(xa, xb), np.append(ya, yb)]).T
    y_true = np.hstack([np.ones(na, dtype=np.intp), -1 * np.ones(nb, dtype=np.intp)])

    X += np.random.uniform(-w / 2, w / 2, X.shape)

    # Filter noise at the beginning and end of each moon
    X[:na, 1] = np.where(X[:na, 1] < 0, 0, X[:na, 1])
    X[na:, 1] = np.where(X[na:, 1] > -d, -d, X[na:, 1])

    return X, y_true
