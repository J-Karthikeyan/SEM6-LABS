import matplotlib.pyplot as plt
import torch
import torch.nn as nn

X = torch.Tensor([[0, 0], [0, 1], [1, 0], [1, 1]])
y = torch.Tensor([0, 1, 1, 0]).view(-1, 1)
print(X.shape, y.shape)

class XORClassifier(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.linear1 = nn.Linear(2,2)
        self.sigmoid = nn.Sigmoid()
        self.linear2 = nn.Linear(2, 1)
    def forward(self, x):
        x = self.linear1(x)
        x = self.sigmoid(x)
        x = self.linear2(x)
        return x

model = XORClassifier()

#  
def init_weights(model):
    for m in model.modules():
        if isinstance(m, nn.Linear):
            m.weight.data.normal_(0, 1)
init_weights(model)

print(model.state_dict())
loss_fn = nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr= 0.01)

epochs = 1000

losses = []
for epoch in range(epochs):
    y_pred = model(X)
    loss = loss_fn(y, y_pred)
    losses.append(loss.detach().numpy())
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if (epoch+1) % 100 == 0:
        print(f"Epoch {epoch + 1}, Loss: {loss}")

with torch.inference_mode():
    y_pred_test = model(X)
    print(y_pred_test)

plt.plot(losses)
plt.show()

print(torch.round(y_pred_test).detach().numpy())

print(list(model.modules()))
"""
OrderedDict({'linear1.weight': tensor([[-0.4349,  0.3487],
        [-0.2585,  0.1147]]), 'linear1.bias': tensor([ 0.6899, -0.3311]), 'linear2.weight': tensor([[-0.9561,  1.3825]]), 'linear2.bias': tensor([0.4197])})
"""
