import numpy as np

import randomname

from . import activations


class Layer:
    def __init__(self, units, trainable, name=randomname.get_name()):
        self.units = units
        self.trainable = trainable
        self.name = name


class Input(Layer):
    def __init__(self, units, **kwargs):
        super().__init__(units=units, trainable=False, **kwargs)


class Dense(Layer):
    def __init__(self, units, activation, eta=1e-3, alpha=0.9, last=False, **kwargs):
        # 0 <= alpha < 1
        super().__init__(units=units, trainable=True, **kwargs)
        self.inputs = None
        self.w = None
        self.eta = eta
        self.alpha = alpha
        self.last = last

        f, df = activations.get(activation)
        self.activation = f
        self.dactivation = df

        self._x = None  # Last neuron input
        self._v = None  # Last induced local field
        self._delta = 0  # Last weight correction

    def forward(self, x):
        if self.w is None:
            # Since the network is fully connected, the input vector for the neurons in
            # a layer are equal, therefore, have the same size. Here we use a matrix of
            # shape (units, inputs + 1) to represent all the weights, including the bias
            shape = (self.units, self.inputs + 1)
            self.w = np.random.uniform(low=-0.5, high=0.5, size=shape)

        # Add fixed bias input (+1)
        self._x = np.insert(x, 0, 1, axis=0)

        # Calculate induced local field
        self._v = self.w @ self._x.T

        # Apply the activation function in the induced local field
        y = self.activation(self._v)

        return y

    def backward(self, error):
        # Stochastic gradient descent: sgd

        # Compute the local gradients
        grads = error * self.dactivation(self._v)

        # Adjust the synaptic weights of the layer
        for i in range(self.units):
            self._delta = self._delta * self.alpha + self.eta * grads[i] * self._x
            self.w[i] += self._delta

        # Calculate the weighted sum of the local gradients, i.e., the error to be
        # propagated backwards
        error = np.array([])
        for i in range(self.inputs):
            # Delta for each neuron k multiplied by the weights of each neuron k that
            # connects with each neuron j (that's why we get each weight column w[:, i]
            error = np.append(error, sum(grads * self.w[:, i]))

        return error
