import sys

from PySide6.QtCore import Qt
from PySide6.QtWidgets import (
    QApplication,
    QCheckBox,
    QComboBox,
    QLineEdit,
    QListWidget,
    QMainWindow,
    QVBoxLayout,
    QWidget,
)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("My App")

        layout = QVBoxLayout()

        checkbox = QCheckBox("This is a checkbox")
        checkbox.setCheckState(Qt.CheckState.Checked)

        # For tristate: checkbox.setCheckState(Qt.CheckState.PartiallyChecked)
        # Or: checkbox.setTristate(True)
        checkbox.stateChanged.connect(self.show_state)
        layout.addWidget(checkbox)

        combobox = QComboBox()
        combobox.addItems(["One", "Two", "Three"])

        # The default signal from currentIndexChanged sends the index
        combobox.currentIndexChanged.connect(self.index_changed)

        # The same signal can send a text string
        combobox.currentTextChanged.connect(self.text_changed)
        layout.addWidget(combobox)

        listwidget = QListWidget()
        listwidget.addItems(["One", "Two", "Three"])

        # In QListWidget there are two separate signals for the item
        listwidget.currentItemChanged.connect(self.index_changed_list)
        listwidget.currentTextChanged.connect(self.text_changed)
        layout.addWidget(listwidget)

        self.lineedit = QLineEdit()
        self.lineedit.setMaxLength(10)
        self.lineedit.setPlaceholderText("Enter your text")

        # self.lineedit.setReadOnly(True) # uncomment this to make readonly

        self.lineedit.returnPressed.connect(self.return_pressed)
        self.lineedit.selectionChanged.connect(self.selection_changed)
        self.lineedit.textChanged.connect(self.text_changed_line)
        self.lineedit.textEdited.connect(self.text_edited)
        layout.addWidget(self.lineedit)

        central_widget = QWidget()
        central_widget.setLayout(layout)

        self.setCentralWidget(central_widget)

    def show_state(self, state):
        print(state == Qt.CheckState.Checked.value)
        print(state)

    def index_changed(self, index):  # index is an int starting from 0
        print(index)

    def index_changed_list(self, index):  # index is an int starting from 0
        print(index.text())

    def text_changed(self, text):  # text is a str
        print(text)

    def return_pressed(self):
        print("Return pressed!")
        self.lineedit.setText("BOOM!")

    def selection_changed(self):
        print("Selection changed")
        print(self.lineedit.selectedText())

    def text_changed_line(self, text):
        print("Text changed...")
        print(text)

    def text_edited(self, text):
        print("Text edited...")
        print(text)


app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()
