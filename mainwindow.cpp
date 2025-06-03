#include "MainWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QFormLayout *formLayout = new QFormLayout;

    idInput = new QLineEdit;
    descInput = new QLineEdit;
    locInput = new QLineEdit;

    formLayout->addRow("ID:", idInput);
    formLayout->addRow("Description:", descInput);
    formLayout->addRow("Location:", locInput);

    QPushButton *addButton = new QPushButton("Add Item");
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);

    findIdInput = new QLineEdit;
    QPushButton *findButton = new QPushButton("Find by ID");
    connect(findButton, &QPushButton::clicked, this, &MainWindow::onFindItemClicked);

    removeIdInput = new QLineEdit;
    QPushButton *removeButton = new QPushButton("Remove by ID");
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItemClicked);

    itemList = new QListWidget;

    layout->addLayout(formLayout);
    layout->addWidget(addButton);
    layout->addWidget(findIdInput);
    layout->addWidget(findButton);
    layout->addWidget(removeIdInput);
    layout->addWidget(removeButton);
    layout->addWidget(itemList);

    setCentralWidget(centralWidget);

    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Exit", this, &QWidget::close);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("About", [this]() {
        QMessageBox::about(this, "About", "Your Name - Assignment Congo GUI");
    });
}

MainWindow::~MainWindow() {}

void MainWindow::onAddItemClicked() {
    std::string id = idInput->text().toStdString();
    std::string desc = descInput->text().toStdString();
    std::string loc = locInput->text().toStdString();
    try {
        manager.addItem(id, desc, loc);
        refreshItemList();
    } catch (const std::exception &e) {
        showError(e.what());
    }
}

void MainWindow::onFindItemClicked() {
    std::string id = findIdInput->text().toStdString();
    try {
        std::shared_ptr<StoredItem> item = manager.findById(id);
        QMessageBox::information(this, "Item Found",
                                 QString::fromStdString("ID: " + item->getId() + "\nDescription: " +
                                                        item->getDescription() + "\nLocation: " + item->getLocation()));
    } catch (const std::exception &e) {
        showError(e.what());
    }
}

void MainWindow::onRemoveItemClicked() {
    std::string id = removeIdInput->text().toStdString();
    try {
        manager.removeItem(id);
        refreshItemList();
    } catch (const std::exception &e) {
        showError(e.what());
    }
}

void MainWindow::refreshItemList() {
    itemList->clear();
    std::map<std::string, std::shared_ptr<StoredItem>> items = manager.listItemsByDescription();
    for (const auto &pair : items) {
        itemList->addItem(QString::fromStdString(pair.second->getDescription() +
                                                 " (ID: " + pair.second->getId() + ") - Loc: " +
                                                 pair.second->getLocation()));
    }
}

void MainWindow::showError(const QString &message) {
    QMessageBox::critical(this, "Error", message);
}
