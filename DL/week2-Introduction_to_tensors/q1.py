import torch

a = torch.tensor([2.7], requires_grad=True)
b = torch.tensor([1.8], requires_grad=True)

x = 2 * a + 3 * b 
y = 5 * a * a + 3 * b * b * b
z = 2 * x + 3 * y

z.backward()

print("Autograd: ")
print(f"dz/da= {a.grad}")
print(f"dz/db= {b.grad}")

def manual_gradient() -> None:
    dx_da = 2
    dx_db = 3
    dy_da = 10 * a
    dy_db = 9 * b * b

    dz_dx = 2
    dz_dy = 3

    dz_da = dz_dx * dx_da + dz_dy * dy_da
    dz_db = dz_dx * dx_db + dz_dy * dy_db
    
    return dz_da, dz_db

dz_da, dz_db = manual_gradient()
print(f"Manual Gradient: \ndz/da = {dz_da}\ndz_db = {dz_db}")


""" out
Autograd: 
dz/da= tensor([85.])
dz/db= tensor([93.4800])

Manual Gradient: 
dz/da = tensor([85.], grad_fn=<AddBackward0>)
dz_db = tensor([93.4800], grad_fn=<AddBackward0>)
"""
