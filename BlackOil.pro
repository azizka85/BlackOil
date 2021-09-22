TEMPLATE = subdirs

SUBDIRS += \
    BlackOil \
    Data \
    Desktop \
    Model \
    Test

Model.depends = Data
Test.depends = Data Model
Desktop.depends = Data Model
BlackOil.depends = Data Model Desktop
