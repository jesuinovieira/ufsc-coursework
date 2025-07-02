[![Python 3.9](https://img.shields.io/badge/python-3.9-blue)](https://img.shields.io/badge/python-3.9%20%7C%203.7%20%7C%203.9-blue)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)

# MLP

Implementation of the MLP neural network, following the definitions provided by [1]. The report (in Portuguese) is available at [docs/relatorio.pdf](docs/relatorio.pdf).

> [1] Haykin, S. S. (2009), Neural networks and learning machines, Pearson Education, Upper Saddle River, NJ.

## Leftovers

- [ ] Cross-validation
- [ ] Crossentropy loss function
- [ ] Softmax as output layer
- [ ] Leaky relu
- [ ] Better stopping criteria
- [ ] Batches and mini batches

# Install

Set up a clean python environment and install dependencies:

```bash
pip install -r requirements.txt
```

# Usage

```python
import mlp
import utils

X_train, X_test, y_train, y_test = utils.loadmnist("data")

model = mlp.MLP()

model.add(mlp.layers.Input(units=784))
model.add(mlp.layers.Dense(units=128, eta=1e-5, alpha=0.9, activation="tanh"))
model.add(mlp.layers.Dense(units=10, eta=1e-5, alpha=0.9, activation="tanh"))

model.compile(loss="mse", tol=0.0)
model.fit(X_train, y_train, epochs=50)

acc, loss = model.evaluate(X_test, y_test)
```
