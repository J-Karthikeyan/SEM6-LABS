import torch

W = torch.tensor([1.05, 0.95, 1], requires_grad=True)
X = torch.tensor([1., 2., 3.], requires_grad=True)
b = torch.tensor([7.8], requires_grad=True)

u = W @ X
v = u + b
a = torch.nn.functional.sigmoid(v)

a.backward()

print("Autograd: ")
print(f"da/dx = {X.grad}\n"
      f"da/dw = {W.grad}\n"
      f"da/db = {b.grad}")

def analytial_gradient():
    da_dv = (1 - a) * a
    
    dv_du = 1
    dv_db = 1

    du_dw = X
    du_dx = W

    da_dx = da_dv * dv_du * du_dx
    da_dw = da_dv * dv_du * du_dw
    da_db = da_dv * dv_db

    return da_dx, da_dw, da_db

da_dx, da_dw, da_db = analytial_gradient()

print("Analytical: ")
print(f"da/dx = {da_dx}\n"
      f"da/dw = {da_dw}\n"
      f"da/db = {da_db}")

""" out

Autograd: 
da/dx = tensor([1.0500, 0.9500, 1.0000])
da/dw = tensor([1., 2., 3.])
da/db = tensor([1.])

Analytical: 
da/dx = tensor([1.0500, 0.9500, 1.0000], grad_fn=<MulBackward0>)
da/dw = tensor([1., 2., 3.], grad_fn=<MulBackward0>)
da/db = tensor([1])
"""
