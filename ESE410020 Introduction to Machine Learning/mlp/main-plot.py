import os
import json

import mlp
import plot
import utils


logger = utils.getlogger(__name__)


def getmodel(folder, files):
    rfile = [file for file in files if "results.json" in file][0]
    rfile = f"{folder}/{rfile}"

    mfile = [file for file in files if "E250" in file][0]
    mfile = f"{folder}/{mfile}"

    model = mlp.MLP.load(mfile)

    with open(rfile, "r") as f:
        results = json.load(f)

    return model, results


def groupby(models, results):
    tmp = {}
    for model, result in zip(models, results):
        nlayers = len(result["neurons"])
        nunits = sum(result["neurons"])

        key = f"{nlayers}L-{nunits}N"

        if key not in tmp.keys():
            tmp[key] = [(model, result)]
        else:
            tmp[key].append((model, result))

    return tmp


def main():
    models = []
    results = []

    for root, dirs, files in os.walk("checkpoints"):
        if root == "checkpoints":
            continue

        model, result = getmodel(root, files)

        models.append(model)
        results.append(result)

    tmp = groupby(models, results)

    for key, value in tmp.items():
        plot.lc(key, value)
    plot.heatmap(tmp)


if __name__ == "__main__":
    main()
