import torch
import numpy as np

def f(x):
    return torch.exp(- torch.square(x) - 2 * x - torch.sin(x))

x = torch.tensor([0.42], requires_grad=True)
y = f(x)

y.backward()

print(f"Autograd:\ndy/dx = {x.grad}\n")

def analytical_grad():
    x_ = x.detach().numpy()
    a = -x_ * x_
    b = -2 * x_
    c = -np.sin(x_)
    y = np.exp(a + b + c)

    da_dx = -2 * x_
    db_dx = -2
    dc_dx = -np.cos(x_)

    dx_dy = y * (da_dx + db_dx + dc_dx)

    return dx_dy

print(f"Analytical:\ndy/dx = {analytical_grad()}\n")

