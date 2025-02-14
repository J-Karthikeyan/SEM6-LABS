import torch
import torch.nn as nn
import torchvision.datasets as datasets
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
from matplotlib import pyplot as plt

transform = transforms.Compose([transforms.ToTensor()])

mnist_train = datasets.MNIST(root='./data', train=True, transform=transform)
mnist_test = datasets.MNIST(root='./data', train=False, transform=transform)

print("Shape =", mnist_train[0][0].shape)
print("Type =", type(mnist_train[0]))
print("Training size =", len(mnist_train))  
print("Testing size =", len(mnist_test))

batch_size = 32  
train_loader = DataLoader(mnist_train, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(mnist_test, batch_size=batch_size)


class CNNClassifier(nn.Module):
    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(
            nn.Conv2d(1, 64, kernel_size=3),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(64, 128, kernel_size=3),
            nn.ReLU(),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(128, 64, kernel_size=3),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        )

        self.flatten_size = self._get_flatten_size()

        self.classification_head = nn.Sequential(
            nn.Linear(self.flatten_size, 20, bias=True),
            nn.ReLU(),
            nn.Linear(20, 10, bias=True)
        )

    def _get_flatten_size(self):
        with torch.no_grad():
            x = torch.randn(1, 1, 28, 28)  
            x = self.net(x)
            return x.numel() 

    def forward(self, x):
        features = self.net(x)
        features = features.view(features.size(0), -1)  
        return self.classification_head(features)


# Set Device
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("Using device:", device)

model = CNNClassifier().to(device)
criterion = nn.CrossEntropyLoss()
optim = torch.optim.Adam(model.parameters(), lr=0.001)

print("Number of parameters =", sum(p.numel() for p in model.parameters()))


def train_one_epoch(epoch_idx):
    total_loss = 0
    total_correct = 0
    total_samples = 0

    model.train() 

    for inputs, labels in train_loader:
        inputs, labels = inputs.to(device), labels.to(device)  
        optim.zero_grad()
        outputs = model(inputs)

        loss = criterion(outputs, labels)
        loss.backward()
        optim.step()

        total_loss += loss.item()
        _, predicted = torch.max(outputs, 1)
        total_correct += (predicted == labels).sum().item()
        total_samples += labels.size(0)

    accuracy = (total_correct / total_samples) * 100
    return total_loss / len(train_loader), accuracy


epochs = 15
loss_values = []
print("Initializing training on device:", device)

for epoch in range(epochs):
    avg_loss, accuracy = train_one_epoch(epoch)
    loss_values.append(avg_loss)
    print(f"Epoch {epoch + 1}/{epochs}, Loss: {avg_loss:.4f}, Accuracy: {accuracy:.2f}%")

plt.plot(loss_values)
plt.grid()
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Training Loss Curve")
plt.show()
