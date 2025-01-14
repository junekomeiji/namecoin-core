#include <qt/buynamespage.h>
#include <qt/forms/ui_buynamespage.h>

#include <interfaces/node.h>
#include <logging.h>
#include <qt/configurenamedialog.h>
#include <qt/guiutil.h>
#include <qt/nametablemodel.h>
#include <qt/platformstyle.h>
#include <qt/walletmodel.h>
#include <rpc/protocol.h>
#include <names/applications.h>

#include <names/encoding.h>
#include <univalue.h>

#include <string>
#include <algorithm>

#include <QMessageBox>

//ascii -> old domain system
//domain -> domain from scratch (without .bit)
//hex -> hex
BuyNamesPage::BuyNamesPage(const PlatformStyle *platformStyle, QWidget *parent) :
    QWidget(parent),
    platformStyle(platformStyle),
    ui(new Ui::BuyNamesPage),
    walletModel(nullptr)
{
    ui->setupUi(this);

    ui->registerNameButton->hide();
    
    connect(ui->registerNameDomain, &QLineEdit::textEdited, this, &BuyNamesPage::onDomainNameEdited);
    connect(ui->registerNameAscii, &QLineEdit::textEdited, this, &BuyNamesPage::onAsciiNameEdited);
    connect(ui->registerNameHex, &QLineEdit::textEdited, this, &BuyNamesPage::onHexNameEdited);
    connect(ui->registerNameButton, &QPushButton::clicked, this, &BuyNamesPage::onRegisterNameAction);

    ui->registerNameDomain->installEventFilter(this);
    ui->registerNameAscii->installEventFilter(this);
    ui->registerNameHex->installEventFilter(this);
}

BuyNamesPage::~BuyNamesPage()
{
    delete ui;
}

void BuyNamesPage::setModel(WalletModel *walletModel)
{
    this->walletModel = walletModel;
}

bool BuyNamesPage::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        if (object == ui->registerNameAscii)
        {
            ui->registerNameButton->setDefault(true);
        }

        if (object == ui->registerNameHex)
        {
            ui->registerNameButton->setDefault(true);
        }

        if (object == ui->registerNameDomain)
        {
            ui->registerNameButton->setDefault(true);
        }

    }
    return QWidget::eventFilter(object, event);
}

void BuyNamesPage::onAsciiNameEdited(const QString &name)
{
    if (!walletModel)
        return;

    if(!name.startsWith("d/"))
    {
         ui->statusLabel->setText(tr("%1 does not begin with /d!").arg(name));   
    }
    else
    {
        QString domain = name.right(name.size()-2);
        QString availableError = name_available(domain);
        ui->registerNameHex->setText("642f" + NameTableModel::asciiToHex(domain));
        ui->registerNameDomain->setText(domain + ".bit");

        if (availableError.isEmpty())
        {
            ui->statusLabel->setText(tr("%1 is available to register!").arg(name));
            ui->registerNameButton->show();
        }
        else
        {
            ui->statusLabel->setText(availableError);
            ui->registerNameButton->hide();
        }

    }
    
}

void BuyNamesPage::onHexNameEdited(const QString &name)
{

    if (!walletModel)
        return;

    //check if it's even a valid hexdomain
    QString ascii = NameTableModel::asciiToHex(name);
    if(!std::all_of(name.toStdString().begin(), name.toStdString().end(), ::isxdigit))
    {
        ui->statusLabel->setText(tr("%1 is not a valid hexadecimal entry!").arg(name));
    } 
    else 
    {
        QString availableError = name_available(ascii);
        ui->registerNameAscii->setText("d/" + NameTableModel::hexToAscii(name));
        ui->registerNameDomain->setText(NameTableModel::hexToAscii(name) + ".bit");
    
        if (availableError.isEmpty())
        {
            ui->statusLabel->setText(tr("%1 is available to register!").arg(name));
            ui->registerNameButton->show();
        }
        else
        {
            ui->statusLabel->setText(availableError);
            ui->registerNameButton->hide();
        }
    }

}

void BuyNamesPage::onDomainNameEdited(const QString &name){
    
    if (!walletModel)
        return;

    //check if it even ends with .bit
    if(!name.endsWith(".bit"))
    {
        ui->statusLabel->setText(tr("%1 does not end with .bit!").arg(name));
    } 
    else 
    {
        QString domain = name.left(name.size()-4);
        QString availableError = name_available(domain);
        ui->registerNameAscii->setText("d/" + domain);
        ui->registerNameHex->setText("642f" + NameTableModel::asciiToHex(domain));
    
        if (availableError.isEmpty())
        {
            ui->statusLabel->setText(tr("%1 is available to register!").arg(name));
            ui->registerNameButton->show();
        }
        else
        {
            ui->statusLabel->setText(availableError);
            ui->registerNameButton->hide();
        }
    }
}

void BuyNamesPage::onRegisterNameAction()
{
    if (!walletModel)
        return;

    QString input, name;
    
    name = ui->registerNameAscii->text();
    
    WalletModel::UnlockContext ctx(walletModel->requestUnlock());
    if (!ctx.isValid())
        return;

    ConfigureNameDialog dlg(platformStyle, name, "", this);
    dlg.setModel(walletModel);

    if (dlg.exec() != QDialog::Accepted)
        return;

    const QString &newValue = dlg.getReturnData();
    const std::optional<QString> transferToAddress = dlg.getTransferTo();

    const QString err_msg = this->firstupdate(name, newValue, transferToAddress);
    if (!err_msg.isEmpty() && err_msg != "ABORTED")
    {
        QMessageBox::critical(this, tr("Name registration error"), err_msg);
        return;
    }

}

// Returns empty string if available, otherwise a description of why it is not
// available.
QString BuyNamesPage::name_available(const QString &name) const
{
    const std::string strName = name.toStdString();
    LogDebug(BCLog::QT, "wallet attempting name_show: name=%s\n", strName);

    UniValue params(UniValue::VOBJ);

    try
    {
        const QString hexName = NameTableModel::asciiToHex(name);
        params.pushKV ("name", hexName.toStdString());
    }
    catch (const InvalidNameString& exc)
    {
        return tr ("Name was invalid ASCII.");
    }

    UniValue options(UniValue::VOBJ);
    options.pushKV ("nameEncoding", "hex");
    params.pushKV ("options", options);

    const std::string walletURI = "/wallet/" + walletModel->getWalletName().toStdString();

    try
    {
        walletModel->node().executeRpc("name_show", params, walletURI);
    }
    catch (const UniValue& e)
    {
        const UniValue code = e.find_value("code");
        const int codeInt = code.getInt<int>();
        if (codeInt == RPC_WALLET_ERROR)
        {
            // Name doesn't exist, so it's available.
            return QString("");
        }

        const UniValue message = e.find_value("message");
        const std::string errorStr = message.get_str();
        LogDebug(BCLog::QT, "name_show error: %s\n", errorStr);
        return QString::fromStdString(errorStr);
    }

    return tr("%1 is already registered, sorry!").arg(name);
}

QString BuyNamesPage::firstupdate(const QString &name, const std::optional<QString> &value, const std::optional<QString> &transferTo) const
{
    const std::string strName = name.toStdString();
    LogDebug(BCLog::QT, "wallet attempting name_firstupdate: name=%s\n", strName);

    UniValue params(UniValue::VOBJ);

    try
    {
        const QString hexName = NameTableModel::asciiToHex(name);
        params.pushKV ("name", hexName.toStdString());
    }
    catch (const InvalidNameString& exc)
    {
        return tr ("Name was invalid ASCII.");
    }

    UniValue options(UniValue::VOBJ);
    options.pushKV ("nameEncoding", "hex");

    if (value)
    {
        try
        {
            const QString hexValue = NameTableModel::asciiToHex(value.value());
            params.pushKV ("value", hexValue.toStdString());
        }
        catch (const InvalidNameString& exc)
        {
            return tr ("Value was invalid ASCII.");
        }

        options.pushKV ("valueEncoding", "hex");
    }

    if (transferTo)
    {
        options.pushKV ("destAddress", transferTo.value().toStdString());
    }

    params.pushKV ("options", options);

    const std::string walletURI = "/wallet/" + walletModel->getWalletName().toStdString();

    try {
        walletModel->node().executeRpc("name_firstupdate", params, walletURI);
    }
    catch (const UniValue& e) {
        const UniValue message = e.find_value("message");
        const std::string errorStr = message.get_str();
        LogDebug(BCLog::QT, "name_firstupdate error: %s\n", errorStr);
        return QString::fromStdString(errorStr);
    }
    return tr ("");
}
