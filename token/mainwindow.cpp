// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QString>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QComboBox>
#include <QOverload>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QTextCharFormat>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("JWT Generator");
    QIcon icon("C:\\Users\\pc\\Desktop\\c++rapport\\j.png");
    this->setWindowIcon(icon);

    ////save button
    saveButton = new QPushButton("Save", this);
    saveButton->setGeometry(0,0, 75, 23);


    tokenTextEdit = findChild<QTextEdit*>("TokenTextEdit");
    headerTextEdit = findChild<QTextEdit*>("headerTextEdit");
    payloadTextEdit = findChild<QTextEdit*>("PayloadTextEdit");
    signatureTextEdit = findChild<QTextEdit*>("SIgnatureTextEdit");



    headerLabel = findChild<QLabel*>("HeaderLabel");
    payloadLabel = findChild<QLabel*>("PayloadLabel");
    signatureLabel = findChild<QLabel*>("SignatureLabel");
    encodedLabel = findChild<QLabel*>("EncodedLabel");
    decodedLabel = findChild<QLabel*>("DecodedLabel");

    QFont fontt = encodedLabel->font();
    fontt.setPointSize(13);

    headerLabel->setText("HEADER: ALGORITHM & TOKEN TYPE");
    payloadLabel->setText("PAYLOAD: DATA");
    signatureLabel->setText("VERIFY SIGNATURE");
    encodedLabel->setText("Encoded");
    decodedLabel->setText("Decoded");

    ///changement de la taille des titres
    encodedLabel->setFont(fontt);
    decodedLabel->setFont(fontt);

    ///l'emplacement des titres et des textedit
    headerLabel->setGeometry(400, 100, 391, 21);
    payloadLabel->setGeometry(400, 250, 391, 16);
    signatureLabel->setGeometry(400, 400, 391, 16);
    encodedLabel->setGeometry(3, 40, 100, 75);
    decodedLabel->setGeometry(400, 40, 100, 75);

    headerTextEdit->setGeometry(400, 130, 391, 100);
    payloadTextEdit->setGeometry(400, 270, 391, 121);
    signatureTextEdit->setGeometry(400, 420, 391, 131);
    tokenTextEdit->setGeometry(3, 90, 390, 461);

    ///le input du secret
    signatureInput = new QTextEdit(this);
    signatureInput->setPlaceholderText("Enter secret");
    signatureInput->setGeometry(415, 476, 160, 30);
    QString signatureContent = "HMACSHA256(\n  base64UrlEncode(header) + \".\" +\n  base64UrlEncode(payload),\n\n\n)";
    QTextCharFormat fo;
    fo.setForeground(Qt::blue);

    signatureTextEdit->clear();
    signatureTextEdit->setCurrentCharFormat(fo);
    signatureTextEdit->insertPlainText(signatureContent);
    signatureTextEdit->setReadOnly(true);



    ////le message de verification de la signature
    verification = new QLabel(this);
    verification->setText("Signature Verified");
    QFont font = verification->font();
    font.setPointSize(12);
    verification->setFont(font);
    verification->setGeometry(342, 552, 300, 40);
    verification->setStyleSheet("QLabel { color : green; }");



    ///L'initialisation du payload
    QString payloadContent = payloadTextEdit->toPlainText();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(payloadContent.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();


    QJsonObject initalpayloadObject;
    initalpayloadObject["sub"] = jsonObject.value("sub").toString();
    initalpayloadObject["name"] = jsonObject.value("name").toString();
    initalpayloadObject["iss"] = jsonObject.value("iss").toString();

    // Convert the payload JSON to a string
    QString payloadString = QJsonDocument(initalpayloadObject).toJson(QJsonDocument::Indented);
    QTextCharFormat forma;
    forma.setForeground(Qt::magenta);

    /// changement du couleur
    payloadTextEdit->clear();
    payloadTextEdit->setCurrentCharFormat(forma);
    payloadTextEdit->insertPlainText(payloadString);


    ///L'initialisation du header
    QString headerContent = headerTextEdit->toPlainText();

    QJsonDocument jsonDo = QJsonDocument::fromJson(headerContent.toUtf8());
    QJsonObject jsonObjec = jsonDo.object();

    QJsonObject initalheaderObject;
    initalheaderObject["alg"] = jsonObjec.value("alg").toString();  // Use the existing value or set a default
    initalheaderObject["typ"] = jsonObjec.value("typ").toString(); // Use the existing value or set a default

    ///changement du couleur
    QString headerString = QJsonDocument(initalheaderObject).toJson(QJsonDocument::Indented);
    QTextCharFormat format;
    format.setForeground(Qt::red);

    // Apply the formatting to the headerTextEdit
    headerTextEdit->clear();
    headerTextEdit->setCurrentCharFormat(format);
    headerTextEdit->insertPlainText(headerString);


    /// ///////////algorithms
    algo=new QLabel(this);
    algo->setText("Algorithms");
    algo->setGeometry(330, 25, 150, 25);

    algorithmComboBox = new QComboBox(this);
    algorithmComboBox->setGeometry(400, 25, 80, 25);
    algorithmComboBox->addItem("HS256");
    algorithmComboBox->addItem("HS384");
    algorithmComboBox->addItem("HS512");

    // Connect the signal for item selection to a slot
    connect(algorithmComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::onAlgorithmSelected);
    connect(headerTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
    connect(payloadTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
    connect(signatureInput, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);


    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);

    connect(tokenTextEdit, &QTextEdit::textChanged, this, &MainWindow::onTokenChanged);

}
void MainWindow::onAlgorithmSelected(int index)
{
    disconnect(tokenTextEdit, &QTextEdit::textChanged, this, &MainWindow::onTokenChanged);
    connect(headerTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
    connect(payloadTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);

    // Get the selected algorithm name from the combo box
    QString selectedAlgorithm = algorithmComboBox->itemText(index);

    // Parse the JSON content of the header
    QJsonDocument jsonDoc = QJsonDocument::fromJson(headerTextEdit->toPlainText().toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject headerObject = jsonDoc.object();
        headerObject["alg"] = selectedAlgorithm;  // Use the existing value or set a default
        headerObject["typ"] = headerObject.value("typ").toString(); // Use the existing value or set a default

        // Convert the header JSON to a string
        QString headerString = QJsonDocument(headerObject).toJson(QJsonDocument::Indented);

        // Create a QTextCharFormat to set the text color
        QTextCharFormat format;
        format.setForeground(Qt::red);

        // Disconnect the textChanged signal temporarily

        // Apply the formatting to the headerTextEdit and set the content
        headerTextEdit->clear();
        headerTextEdit->setCurrentCharFormat(format);
        headerTextEdit->setPlainText(headerString);


        QStringList headerValues;

        for (auto it = headerObject.begin(); it != headerObject.end(); ++it) {
            headerValues.append(it.value().toString());
        }
        ///
        //
        QString hmacAlgorithm;
        if (headerValues[0] == "HS256") {
            hmacAlgorithm = "sha256";
        } else if (headerValues[0] == "HS384") {
            hmacAlgorithm = "sha384";
        } else if (headerValues[0] == "HS512") {
            hmacAlgorithm = "sha512";
        }
        QString signatureContent = "HMAC"+hmacAlgorithm.toUpper()+"(\n  base64UrlEncode(header) + \".\" +\n  base64UrlEncode(payload),\n\n\n)";

        QTextCharFormat fo;
        fo.setForeground(Qt::blue);

        // Apply the formatting to the headerTextEdit
        signatureTextEdit->clear();
        signatureTextEdit->setCurrentCharFormat(fo);
        signatureTextEdit->insertPlainText(signatureContent);

        // Reset formatting and update the content of the payloadTextEdit with the updated payload
        fo.clearForeground();
        signatureTextEdit->setCurrentCharFormat(fo);
        signatureTextEdit->setReadOnly(true);

        /////////////
        verification->setText("Signature Verified");
        verification->setStyleSheet("QLabel { color : green; }");
    }
    connect(tokenTextEdit, &QTextEdit::textChanged, this, &MainWindow::onTokenChanged);

}
void MainWindow::colorAndDisplayToken(const std::string &token) {
    // Extracting the header, payload, and signature from the provided token
    QString tokenQString = QString::fromStdString(token);
    QStringList parts = tokenQString.split('.');

    QString headerPart = parts.value(0);
    QString payloadPart = parts.value(1);
    QString signaturePart = parts.value(2);

    // Set the color of each part
    QTextCharFormat headerFormat;
    headerFormat.setForeground(Qt::red);

    QTextCharFormat payloadFormat;
    payloadFormat.setForeground(Qt::magenta);

    QTextCharFormat signatureFormat;
    signatureFormat.setForeground(Qt::blue);

    // Apply formatting to each part
    tokenTextEdit->clear();

    // Header
    tokenTextEdit->setCurrentCharFormat(headerFormat);
    tokenTextEdit->insertPlainText(headerPart);

    // Separator
    tokenTextEdit->insertPlainText(".");

    // Payload
    tokenTextEdit->setCurrentCharFormat(payloadFormat);
    tokenTextEdit->insertPlainText(payloadPart);

    // Separator
    tokenTextEdit->insertPlainText(".");

    // Signature
    tokenTextEdit->setCurrentCharFormat(signatureFormat);
    tokenTextEdit->insertPlainText(signaturePart);
}


void MainWindow::onHeadPaySTextChanged()
{
    disconnect(tokenTextEdit, &QTextEdit::textChanged, this, &MainWindow::onTokenChanged);

    QString headerContent = headerTextEdit->toPlainText();
    QString payloadContent = payloadTextEdit->toPlainText();
    QString secretContent = signatureInput->toPlainText();

    // Parse the JSON content
    QJsonDocument jsonDoc = QJsonDocument::fromJson(headerContent.toUtf8());
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // Get the keys from the payload JSON
        QJsonDocument payloadDoc = QJsonDocument::fromJson(payloadContent.toUtf8());
        if (!payloadDoc.isNull() && payloadDoc.isObject()) {
            QJsonObject payloadObject = payloadDoc.object();
            QJsonObject headerObject = jsonDoc.object();

            // Get the keys and update the content of the tokenTextEdit
            QStringList payloadValues;
            for (auto it = payloadObject.begin(); it != payloadObject.end(); ++it) {
                payloadValues.append(it.value().toString());
            }
            QStringList headerValues;
            for (auto it = headerObject.begin(); it != headerObject.end(); ++it) {
                headerValues.append(it.value().toString());
            }

            // Get the selected algorithm from the combo box
            QString selectedAlgorithm = headerValues[0];

            // Dynamically set the algorithm based on the selected algorithm

            std::string secret = secretContent.toStdString();

            if (selectedAlgorithm == "HS256") {
                auto token = jwt::create()
                                 .set_type(headerValues[1].toStdString())
                                 .set_issuer(payloadValues[0].toStdString())
                                 .set_payload_claim("sub", jwt::claim(payloadValues[2].toStdString()))
                                 .set_payload_claim("name", jwt::claim(payloadValues[1].toStdString()))
                                 .sign(jwt::algorithm::hs256(secret));
                colorAndDisplayToken(token);
            } else if (selectedAlgorithm == "HS384") {
                auto token = jwt::create()
                                 .set_type(headerValues[1].toStdString())
                                 .set_issuer(payloadValues[0].toStdString())
                                 .set_payload_claim("sub", jwt::claim(payloadValues[2].toStdString()))
                                 .set_payload_claim("name", jwt::claim(payloadValues[1].toStdString()))
                                 .sign(jwt::algorithm::hs384(secret));
                colorAndDisplayToken(token);
            } else if(selectedAlgorithm == "HS512") {
                auto token = jwt::create()
                                 .set_type(headerValues[1].toStdString())
                                 .set_issuer(payloadValues[0].toStdString())
                                 .set_payload_claim("sub", jwt::claim(payloadValues[2].toStdString()))
                                 .set_payload_claim("name", jwt::claim(payloadValues[1].toStdString()))
                                 .sign(jwt::algorithm::hs512(secret));
                colorAndDisplayToken(token);
            }
            ////////////
            verification->setText("Signature Verified");
            verification->setStyleSheet("QLabel { color : green; }");
        }
    }
    connect(tokenTextEdit, &QTextEdit::textChanged, this, &MainWindow::onTokenChanged);
}

void MainWindow::onTokenChanged()
{
    // Check if headerTextEdit is valid before using
    try {
        disconnect(headerTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
        disconnect(payloadTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
        QString token = tokenTextEdit->toPlainText();

        auto decoded = jwt::decode(token.toStdString());

        // Extract claims from the decoded token
        std::string subClaim = decoded.get_payload_claim("sub").as_string();
        std::string nameClaim = decoded.get_payload_claim("name").as_string();
        std::string algClaim = decoded.get_header_claim("alg").as_string();
        std::string typClaim = decoded.get_header_claim("typ").as_string();
        std::string issClaim = decoded.get_payload_claim("iss").as_string();

        QString headerContent = headerTextEdit->toPlainText();

        // Parse the JSON content of the header
        QJsonDocument jsonDoc = QJsonDocument::fromJson(headerContent.toUtf8());
        QJsonObject headerObject = jsonDoc.object();
        headerObject["alg"] = QString::fromStdString(algClaim);
        headerObject["typ"] = QString::fromStdString(typClaim);
        QString headerS = QJsonDocument(headerObject).toJson(QJsonDocument::Indented);
        QTextCharFormat format;
        format.setForeground(Qt::red);

        // Apply the formatting to the headerTextEdit
        headerTextEdit->clear();
        headerTextEdit->setCurrentCharFormat(format);
        headerTextEdit->setPlainText(headerS);
        /////////////////////////////
        QString payloadContent = payloadTextEdit->toPlainText();

        // Parse the JSON content of the header
        QJsonDocument pDoc = QJsonDocument::fromJson(payloadContent.toUtf8());
        QJsonObject payloadObject = pDoc.object();
        payloadObject["sub"] = QString::fromStdString(subClaim);
        payloadObject["name"] = QString::fromStdString(nameClaim);
        payloadObject["iss"] = QString::fromStdString(issClaim);
        QString payload = QJsonDocument(payloadObject).toJson(QJsonDocument::Indented);
        QTextCharFormat f;
        f.setForeground(Qt::magenta);

        // Apply the formatting to the headerTextEdit
        payloadTextEdit->clear();
        payloadTextEdit->setCurrentCharFormat(f);
        payloadTextEdit->setPlainText(payload);


        // Verify the signature using the same algorithm and secret key

        QStringList headerValues;
        for (auto it = headerObject.begin(); it != headerObject.end(); ++it) {
            headerValues.append(it.value().toString());
        }

        QString secretContent = signatureInput->toPlainText();
        std::string secret = secretContent.toStdString();
        if(headerValues[0] == "HS256") {
            jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256(secret))
                .verify(decoded);
        }else if(headerValues[0] == "HS384") {
            jwt::verify()
                .allow_algorithm(jwt::algorithm::hs384(secret))
                .verify(decoded);
        }else if(headerValues[0] == "HS512") {
            jwt::verify()
                .allow_algorithm(jwt::algorithm::hs512(secret))
                .verify(decoded);
        }
        QString hm;
        if (headerValues[0] == "HS256") {
            hm = "sha256";
        } else if (headerValues[0] == "HS384") {
            hm = "sha384";
        } else if (headerValues[0] == "HS512") {
            hm = "sha512";
        }
        QString signatureContent = "HMAC"+hm.toUpper()+"(\n  base64UrlEncode(header) + \".\" +\n  base64UrlEncode(payload),\n\n\n)";

        QTextCharFormat fo;
        fo.setForeground(Qt::blue);

        // Apply the formatting to the headerTextEdit
        signatureTextEdit->clear();
        signatureTextEdit->setCurrentCharFormat(fo);
        signatureTextEdit->insertPlainText(signatureContent);

        // Reset formatting and update the content of the payloadTextEdit with the updated payload
        fo.clearForeground();
        signatureTextEdit->setCurrentCharFormat(fo);
        signatureTextEdit->setReadOnly(true);

        verification->setText("Signature Verified");
        verification->setStyleSheet("QLabel { color : green; }");

        connect(payloadTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);
        connect(headerTextEdit, &QTextEdit::textChanged, this, &MainWindow::onHeadPaySTextChanged);

    } catch (const std::exception &e) {
        // Handle decoding error (e.g., invalid token format)
        verification->setText("Invalid Signature");
        verification->setStyleSheet("QLabel { color : red; }");

    }
}
void MainWindow::onSaveButtonClicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Token Content", QDir::homePath(), "Text Files (*.txt)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << tokenTextEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::critical(this, "Error", "Unable to save file.");
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
