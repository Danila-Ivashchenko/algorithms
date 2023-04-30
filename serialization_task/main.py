import struct
from enum import Enum


class Alignment(Enum):
    HORIZONTAL = 1
    VERTICAL = 2


class Widget():

    def __init__(self, parent):
        self.parent = parent
        self.childrens = []

        if self.parent is not None:
            self.parent.add_children(self)

    def add_children(self, children: "Widget"):
        self.childrens.append(children)

    def _to_binary_internal_data(self): 
        return None 

    def to_binary(self):
        class_name = self.__class__.__name__.encode()
        result = struct.pack("i", len(class_name)) + class_name

        internal_data = self._to_binary_internal_data()
        if internal_data != None:
            result += internal_data
        children_data = b"".join([child.to_binary() for child in self.childrens])
        result += struct.pack("i", len(children_data)) + children_data
        return result

    @classmethod
    def from_binary(cls, binary_data, parent=None):
        class_name_length = struct.unpack("i", binary_data[:4])[0]
        cursore_position = 4
        class_name = binary_data[cursore_position:cursore_position + class_name_length].decode()
        cursore_position += class_name_length
        internal_data_length = struct.unpack("i", binary_data[cursore_position:cursore_position + 4])[0]
        cursore_position += 4
        internal_data = binary_data[cursore_position:cursore_position + internal_data_length].decode()
        cursore_position += internal_data_length

        root = None
        if class_name == "MainWindow":
            root = cls(internal_data)
        elif class_name == "Layout":
            root = Layout(parent, internal_data)
        elif class_name == "LineEdit":
            root = LineEdit(parent, internal_data)
        elif class_name == "ComboBox":
            root = ComboBox(parent, [internal_data[i] for i in range(len(internal_data)) if i % 2 == 0])

        children_length = struct.unpack("i", binary_data[cursore_position:cursore_position + 4])[0]
        cursore_position += 4
        children_data = binary_data[cursore_position:]

        cursor = 0
        while cursor < children_length:
            _, child_cursor = root.from_binary(children_data[cursor:], parent=root)
            cursor += child_cursor

        return root, cursore_position + cursor

    def __str__(self):
        return f"{self.__class__.__name__}{self.childrens}"

    def __repr__(self):
        return str(self)


class MainWindow(Widget):

    def __init__(self, title: str):
        super().__init__(None)
        self.title = title

    def _to_binary_internal_data(self):
        title_str = self.title.encode()
        return struct.pack("i", len(title_str)) + title_str
    
    def __str__(self):
        return f"{self.__class__.__name__}, \"title\": {self.title}, {self.childrens}"
         


class Layout(Widget):

    def __init__(self, parent, alignment: Alignment):
        super().__init__(parent)
        self.alignment = alignment

    def _to_binary_internal_data(self):
            alignment_value = str(self.alignment.value).encode()
            return struct.pack("i", len(alignment_value)) + alignment_value
    
    def __str__(self):
        return f"{self.__class__.__name__}, \"aligment\": {self.alignment}, {self.childrens}"


class LineEdit(Widget):

    def __init__(self, parent, max_length: int = 10):
        super().__init__(parent)
        self.max_length = max_length

    def _to_binary_internal_data(self):
        max_length = str(self.max_length).encode()
        return struct.pack("i", len(max_length)) + max_length
    
    def __str__(self):
        return f"{self.__class__.__name__}, \"max_length\": {self.max_length}, {self.childrens}"

class ComboBox(Widget):

    def __init__(self, parent, items):
        super().__init__(parent)
        self.items = items

    def _to_binary_internal_data(self):
        items = [str(item) for item in self.items]
        items_str = " ".join(items).encode()
        return struct.pack("i", len(items_str)) + items_str
    
    def __str__(self):
        return f"{self.__class__.__name__}, \"items\": {[item for item in self.items]}, {self.childrens}"


app = MainWindow("Application")
layout1 = Layout(app, Alignment.HORIZONTAL)
layout2 = Layout(app, Alignment.VERTICAL)

edit1 = LineEdit(layout1, 20)
edit2 = LineEdit(layout1, 30)

box1 = ComboBox(layout2, [1, 2, 3, 4])
box2 = ComboBox(layout2, ["a", "b", "c"])

print(app)
print()
bts = app.to_binary()
print(f"Binary data length {len(bts)}")
print(f"Binary data {bts}")
print()
new_app = MainWindow.from_binary(bts)
print(new_app[0])