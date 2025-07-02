import collections
import os

import matplotlib.backends.backend_pdf
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import rcParams
from matplotlib.gridspec import GridSpec


# Set matplotlib runtime configuration
DPI = 200
rcParams["figure.autolayout"] = True
rcParams["figure.figsize"] = (1920 / DPI, 1080 / DPI)
# rcParams["font.family"] = "monospace"


def lc(arch, loft, path="output"):
    loft = splitby(arch, loft)

    file = f"{path}/{arch.lower()}-lc.pdf"
    with matplotlib.backends.backend_pdf.PdfPages(file) as pdf:
        fig = plt.figure()
        gs = GridSpec(2, 2, figure=fig)

        loft = collections.OrderedDict(sorted(loft.items()))

        for i, (key, value) in enumerate(loft.items()):
            ax = fig.add_subplot(gs[0, :] if i == 0 else gs[1, i - 1])

            for model, result in value:
                _lc(ax, model, result)

            ax.set_xlabel("Epochs", fontsize=12)
            ax.set_ylabel("Loss", fontsize=12)
            handles, labels = ax.get_legend_handles_labels()
            labels, handles = zip(*sorted(zip(labels, handles), key=lambda t: t[0]))
            ax.legend(handles, labels, fontsize=12)
            plt.grid()

            if not os.path.isdir(path):
                os.makedirs(path)

        _wrapup(pdf)


def heatmap(tmp, path="output"):
    fig = plt.figure()
    gs = GridSpec(1, 3, figure=fig)

    tmp = collections.OrderedDict(sorted(tmp.items()))
    for i, (arch, loft) in enumerate(tmp.items()):
        ax = fig.add_subplot(gs[0, i])

        etas = []
        alphas = []

        for model, result in loft:
            if result["eta"] not in etas:
                etas.append(result["eta"])
            if result["alpha"] not in alphas:
                alphas.append(result["alpha"])

        etas = sorted(etas)
        alphas = reversed(sorted(alphas))

        df = pd.DataFrame(None, columns=etas, index=alphas)

        for model, result in loft:
            eta = result["eta"]
            alpha = result["alpha"]
            df.at[alpha, eta] = result["testacc"]

        for column in df.columns:
            df[column] = pd.to_numeric(df[column])

        sns.heatmap(
            df, square=True, fmt=".2f", cmap=sns.color_palette("vlag", as_cmap=True),
            annot=True, ax=ax, cbar_kws={"shrink": .3975}, annot_kws={"size": 9}
        )

        ax.set_xlabel("eta", fontsize=12)
        ax.set_ylabel("alpha", fontsize=12)

        title = arch.rsplit("-")[1][:-1] + " neurônios"
        ax.set_title(title, fontsize=12)
        if not os.path.isdir(path):
            os.makedirs(path)

    file = f"{path}/acc.pdf"
    with matplotlib.backends.backend_pdf.PdfPages(file) as pdf:
        _wrapup(pdf, True)


def splitby(arch, loft):
    tmp = {}
    for model, result in loft:
        eta = result["eta"]
        key = f"{arch}-E{eta}"

        if key not in tmp.keys():
            tmp[key] = [(model, result)]
        else:
            tmp[key].append((model, result))

    return tmp


def _wrapup(pdf, tight=False):
    # Save pdf figure and clean up plots
    pdf.savefig(bbox_inches="tight" if tight else None)
    plt.clf()
    plt.close("all")


def _lc(ax, model, result):
    # Plot learning curve
    loss = model.history["loss"]
    alpha = result["alpha"]
    eta = result["eta"]
    epochs = np.arange(1, len(loss) + 1)

    palette = {"0.0": "C0", "0.5": "C1", "0.9": "C2"}
    ax.plot(
        epochs, loss, color=palette[str(alpha)],
        lw=1.5, ls="-", label=f"alpha={round(alpha, 1)}"
    )
    ax.set_title(f"eta = {eta}")
