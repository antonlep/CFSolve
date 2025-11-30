import sys

from PySide6.QtCore import QSize
from PySide6.QtWidgets import (
    QApplication,
    QLabel,
    QLineEdit,
    QMainWindow,
    QVBoxLayout,
    QWidget,
)

import solver

window_titles = [
    "My App",
    "My App",
    "Still My App",
    "Still My App",
    "What on earth",
    "What on earth",
    "This is surprising",
    "This is surprising",
    "Something went wrong",
]


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("My App")

        self.label = QLabel()

        self.input = QLineEdit()
        self.input.textChanged.connect(self.label.setText)

        layout = QVBoxLayout()
        layout.addWidget(self.input)
        layout.addWidget(self.label)

        container = QWidget()
        container.setLayout(layout)

        self.setFixedSize(QSize(400, 300))
        self.setCentralWidget(container)


app = QApplication(sys.argv)

window = MainWindow()
window.show()

# Run the application's event loop
app.exec()

# from gui import show_solution

# mesh = load_mesh("triangle.msh")
# u = solver.solve_poisson(mesh)
# show_solution(mesh, u)

u = solver.add(2, 3)
print(u)
