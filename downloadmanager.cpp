#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open " << filename << " for writing: " << file.errorString();
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void DownloadManager::execute()
{
    /*foreach (QString arg, args) {
        QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
        doDownload(url);
    }*/
    for(int i=0;i<downList.size();i++)
    {
        QUrl url =downList[i];
        doDownload(url);
    }
}

void DownloadManager::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, sslErrors)
        qDebug() << "SSL error: "<<error.errorString();
#else
    Q_UNUSED(sslErrors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        QString save("Download of " + QString(url.toEncoded().constData()) + " failed: " + reply->errorString());
        bar->showMessage(save,10000);
        qDebug() << save;
    } else {
        QString filename;// = saveFileName(url);
        int id = getIdDownFile(url.toString());
        if (id!=-1) filename = saveList[id];
        if (saveToDisk(saveList[0], reply))
        {
           QString save("Download of "+QString(url.toEncoded().constData())+" succeeded (saved to "+filename+")");
           bar->showMessage(save,10000);
           qDebug()<<save;
        }
        isDownload();
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();
}
void DownloadManager::setStatusBar(QStatusBar *bar)
{
    this->bar = bar;
}
int DownloadManager::getIdDownFile(QString file) const
{
    for(int i=0;i<downList.size();i++)
        if (downList[i].compare(file)==0) return i;
    return -1;
}
