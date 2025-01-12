import torch

def f(x):
    return 8 * torch.pow(x, 4) +\
           3 * torch.pow(x, 3) +\
           7 * torch.pow(x, 2) +\
           6 * x\
           + 3

x = torch.tensor([2.0], requires_grad=True)
y = f(x)

y.backward()

print(f"Autograd:\ndy/dx = {x.grad}\n")

def analytical_grad():
    da_dx, db_dx, dc_dx, dd_dx = 32 * torch.pow(x, 3), 9 * torch.pow(x, 2), 14 * x, 6
    
    dx_dy = da_dx + db_dx + dc_dx + dd_dx

    return dx_dy

print(f"Analytical:\ndy/dx = {analytical_grad()}\n")

