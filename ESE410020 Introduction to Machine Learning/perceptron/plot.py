import os

import matplotlib.backends.backend_pdf
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rcParams


# Set matplotlib runtime configuration
DPI = 200
rcParams["figure.autolayout"] = True
rcParams["figure.figsize"] = (1920 / DPI, 986 / DPI)
# rcParams["font.family"] = "monospace"


def results(models, X_test, y_test, path, experiment):
    # Learning curve plots
    fig, ax = plt.subplots()

    for model in models:
        _lc(ax, model)
        plt.ylim(bottom=0)

    ax.set_xlabel("Epochs", fontsize=18)
    ax.set_ylabel("Loss", fontsize=18)
    plt.legend(fontsize=18)
    plt.grid()

    if not os.path.isdir(path):
        os.makedirs(path)

    file = f"{path}/{experiment}-lc.pdf"
    with matplotlib.backends.backend_pdf.PdfPages(file) as pdf:
        _wrapup(pdf)

    # Decisioun boundary plots
    for model in models:
        fig, ax = plt.subplots()
        _db(ax, X_test, y_test, model.history)
        eta = model.history["eta"]

        file = f"{path}/{experiment}-db-{eta:.2e}.pdf"
        with matplotlib.backends.backend_pdf.PdfPages(file) as pdf:
            _wrapup(pdf)


def _wrapup(pdf):
    # Save pdf figure and clean up plots
    pdf.savefig()
    plt.clf()
    plt.close("all")


def _db(ax, X, y, history):
    # Plot decision boundary
    ax.scatter(
        X[y == 1, 0], X[y == 1, 1], c="tab:blue", label="Region A", marker="x", s=20
    )
    ax.scatter(X[y == -1, 0], X[y == -1, 1], c="tab:red", label="Region B", marker="+")

    xtmp = np.arange(min(X.T[0]) - 2, max(X.T[0]) + 2)
    xtmp = np.vstack(xtmp)

    a = np.array(history["a"][:-1])
    b = np.array(history["b"][:-1])
    ytmp = a.T * xtmp + b.T
    ax.plot(xtmp, ytmp, lw=0.5, ls="--", color="gray", label="Decision Boundary (i-th)")

    ytmp = history["a"][-1] * xtmp + history["b"][-1]
    ax.plot(xtmp, ytmp, lw=1.5, ls="-", color="black", label="Decision Boundary")

    ax.set_xlabel("x1")
    ax.set_ylabel("x2")
    ax.legend()

    # Remove duplicated labels
    handles, labels = plt.gca().get_legend_handles_labels()
    newLabels, newHandles = [], []
    for handle, label in zip(handles, labels):
        if label not in newLabels:
            newLabels.append(label)
            newHandles.append(handle)
    ax.legend(newHandles, newLabels)

    plt.xlim(min(X[:, 0]) - 1, max(X[:, 0]) + 1)
    plt.ylim(min(X[:, 1]) - 1, max(X[:, 1]) + 1)


def _lc(ax, model):
    # Plot learning curve
    loss = model.history["loss"]
    eta = model.history["eta"]
    epochs = np.arange(1, len(loss) + 1)

    ax.plot(
        epochs, loss,
        lw=1.5, ls="-", marker="o", markersize=2.5, label=f"eta={eta:.2e}",
    )
