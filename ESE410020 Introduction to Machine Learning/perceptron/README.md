[![Python 3.9](https://img.shields.io/badge/python-3.9-blue)](https://img.shields.io/badge/python-3.9%20%7C%203.7%20%7C%203.9-blue)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)

# Perceptron

Implementation of the perceptron neural network, following the definitions provided by [1]. The report (in Portuguese) is available at [docs/relatorio.pdf](docs/relatorio.pdf).

> [1] Haykin, S. S. (2009), Neural networks and learning machines, Pearson Education, Upper Saddle River, NJ.

## Leftovers

- [ ] Generalize classes (not limited to -1 and 1)
- [ ] Extend support to multi-class problems (not only binary)
- [ ] Implement a baseline model

# Install

Set up a clean python environment and install dependencies:

```bash
pip install -r requirements.txt
```

# Usage

```python
import perceptron
import generator
import utils


X, y = generator.moons(na=1500, nb=1500, d=0.5, r=10, w=6)
X_train, X_test, y_train, y_test = utils.split(X, y, trainsize=1/3)

model = perceptron.Perceptron()
model.compile(eta=1e-5, loss="mse", tol=0.0)
model.fit(X_train, y_train, epochs=50)
acc, loss = model.evaluate(X_test, y_test)
```
