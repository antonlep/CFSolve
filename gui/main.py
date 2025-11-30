import sys

from PySide6.QtCore import QSize
from PySide6.QtWidgets import QApplication, QMainWindow, QPushButton

import solver


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("My App")
        button = QPushButton("Press Me!")
        button.setCheckable(True)
        button.clicked.connect(self.the_button_was_clicked)
        self.setFixedSize(QSize(400, 300))
        self.setCentralWidget(button)

    def the_button_was_clicked(self):
        print("Clicked!")


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
