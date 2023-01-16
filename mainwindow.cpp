#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <gdal_priv.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*查询波段范围值 */
QList<int> const getBandInfoMin( GDALRasterBand* poBand ){
    int bGotMin,bGotMax;
    double adfMinMax[2];
    QList<int> list;
    adfMinMax[0] = poBand->GetMinimum(&bGotMin);
    adfMinMax[1] = poBand->GetMaximum(&bGotMax);
    GDALComputeRasterMinMax((GDALRasterBandH)poBand,TRUE,adfMinMax);
    list<< adfMinMax[0]<< adfMinMax[1];
    return list;
}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    GDALAllRegister();
    QString pic =  QFileDialog::getOpenFileName(this,"选择影像","","Images(*.jpg | *.tif)");
    if (pic.isEmpty()) //如果一个文件都没选
        return;

    std::string pic2 = pic.toStdString();
    const char * pszFile = pic2.c_str();
    GDALDataset* poDataset = (GDALDataset*)GDALOpen(pszFile, GA_ReadOnly);

    const char * driverName = poDataset->GetDriverName();
    std::string str(driverName);
    if(str == "JPEG")
    {

        ui->plainTextEdit->appendPlainText("文件地址 :　" + pic );
        ui->plainTextEdit->appendPlainText("文件类型 :JPEG");
        GDALDataset::Bands poBands = poDataset->GetBands();
        for(int i=1;i<poBands.size()+1;i++){
            GDALRasterBand* poBand = poDataset->GetRasterBand(i);
            ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最小值 : " + QString::number(getBandInfoMin(poBand).first()));
            ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最大值 : " + QString::number(getBandInfoMin(poBand).last()));
        }

        char** papszMetadata = poDataset->GetMetadata(NULL);
        /*获取全部元数据信息*/
//        if(CSLCount(papszMetadata)>0)
//        {
//            for(int i=0;papszMetadata[i]!=NULL;i++)
//                ui->plainTextEdit->appendPlainText(papszMetadata[i]);
//        }

        /* 部分GPS+时间信息 */
        if(CSLCount(papszMetadata)>0)
        {
            for(int i=0;papszMetadata[i]!=NULL;i++){
                QString  info = papszMetadata[i];

                if(info.contains(".",Qt::CaseSensitive)&&info.contains("Altitude",Qt::CaseSensitive))
                {
                    QStringList info_Altitude = info.split("=");
                    ui->plainTextEdit->appendPlainText("海拔高度 : " + info_Altitude[1].replace("(","").replace(")","") + "米");
                };

                if(info.contains(".",Qt::CaseSensitive)&&info.contains("Latitude",Qt::CaseSensitive))
                {
                    QStringList temp1 = info.split("=");
                    QString test = temp1[1].replace("(","").replace(")","");
                    QStringList temp2 = test.split(" ");
                    int Latitude_du = temp2[0].toInt();
                    int Latitude_fen = temp2[1].toInt();
                    float Latitude_miao = temp2[2].toFloat();
                    double Latitude = Latitude_du + Latitude_fen/60.0 + Latitude_miao/3600;
                    ui->plainTextEdit->appendPlainText("经度 : " + QString::number(Latitude,'f',8) );
                }

                if(info.contains(".",Qt::CaseSensitive)&&info.contains("Longitude",Qt::CaseSensitive))
                {
                    QStringList temp1 = info.split("=");
                    QString test = temp1[1].replace("(","").replace(")","");
                    QStringList temp2 = test.split(" ");
                    int Longitude_du = temp2[0].toInt();
                    int Longitude_fen = temp2[1].toInt();
                    float Longitude_miao = temp2[2].toFloat();
                    double Longitude = Longitude_du + Longitude_fen/60.0 + Longitude_miao/3600;
                    ui->plainTextEdit->appendPlainText("纬度 : " + QString::number(Longitude,'f',8) );
                }

                if(info.contains("DateTimeDigitized",Qt::CaseSensitive))
                {
                    QStringList temp1 = info.split("=")[1].split(" ");
                    QString date = temp1[0];
                    QString time = temp1[1];

                   ui->plainTextEdit->appendPlainText("拍摄日期 : " + date );
                   ui->plainTextEdit->appendPlainText("拍摄时间 : " + time );

                }

        }
     }
    }

    if(str =="GTiff" )
    {
        QString Projected = "Projection(1:YES;2:NO) :" + QString::number(poDataset->GetSpatialRef()->IsProjected());
        QString SemiMajor = "长轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMajor(),'f',0);
        QString SemiMinor = "短轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMinor(),'f',9);
        QString GetInvFlattening = "扁率 = " + QString::number(poDataset->GetSpatialRef()->GetInvFlattening(),'f',9);
        double test[6];
        poDataset->GetGeoTransform(test);
        ui->plainTextEdit->appendPlainText(pic + "TIF");
        ui->plainTextEdit->appendPlainText(Projected);
        ui->plainTextEdit->appendPlainText(SemiMajor);
        ui->plainTextEdit->appendPlainText(SemiMinor);
        ui->plainTextEdit->appendPlainText(GetInvFlattening);
        //upleft Coordinate
        ui->plainTextEdit->appendPlainText("upperCoord = " + QString::number(test[0],'f',4));
        ui->plainTextEdit->appendPlainText("leftCoord = " + QString::number(test[3],'f',4));
        //pixel width and height
        ui->plainTextEdit->appendPlainText("pixel width = " + QString::number(test[1],'f',4));
        ui->plainTextEdit->appendPlainText("pixel height = " + QString::number(test[5],'f',4));

        //proj信息
        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("PROJCS")));


        GDALDataset::Bands poBands = poDataset->GetBands();
        for(int i=1;i<poBands.size()+1;i++){
            GDALRasterBand* poBand = poDataset->GetRasterBand(i);
            ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最小值 : " + QString::number(getBandInfoMin(poBand).first()));
            ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最大值 : " + QString::number(getBandInfoMin(poBand).last()));
        }

        //单点查询value值
        GDALRasterBand *poBand = poDataset->GetRasterBand(1);
        int nXSize = poBand->GetXSize();
        float *valueResultList = new float[nXSize];
        poBand->RasterIO(GF_Read,2000,2000,1,1,valueResultList,nXSize,1,GDT_Float32,0,0);
        ui->plainTextEdit->appendPlainText(QString::number(valueResultList[0],'f',0));

    };


/*
    //查询坐标系信息
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PROJCS"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("GEOGCS"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("DATUM"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PRIMEM"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("UNIT"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("AUTHORITY"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PROJECTION"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PARAMETER"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("AXIS"));

     //查询椭球信息
//    qDebug("projected :%d",poDataset->GetSpatialRef()->IsProjected());
//    qDebug("SemiMajor :%f",poDataset->GetSpatialRef()->GetSemiMajor());
//    qDebug("SemiMinor :%.9f",poDataset->GetSpatialRef()->GetSemiMinor());
//    qDebug("GetInvFlattening :%.9f",poDataset->GetSpatialRef()->GetInvFlattening());

    //查询偏移信息
//    qDebug("SRS_PP_CENTRAL_MERIDIAN %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_CENTRAL_MERIDIAN,0.0));
//    qDebug("SRS_PP_STANDARD_PARALLEL_1 %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_STANDARD_PARALLEL_1,0.0));
//    qDebug("SRS_PP_FALSE_EASTING %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_FALSE_EASTING,0.0));
//    qDebug("SRS_PP_FALSE_NORTHING %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_FALSE_NORTHING,0.0));

    //
//    qDebug("%f",poDataset->GetSpatialRef()->GetLinearUnits());

    //查询value范围
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//    int bGotMin,bGotMax;
//    double adfMinMax[2];
//    adfMinMax[0] = poBand->GetMinimum(&bGotMin);
//    adfMinMax[1] = poBand->GetMaximum(&bGotMax);
//    GDALComputeRasterMinMax((GDALRasterBandH)poBand,TRUE,adfMinMax);
//    qDebug("Min=%.3f,Max=%.3f",adfMinMax[0],adfMinMax[1]);


//    QString Projected = "Projection(1:YES;2:NO) :" + QString::number(poDataset->GetSpatialRef()->IsProjected());
//    QString SemiMajor = "长轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMajor(),'f',0);
//    QString SemiMinor = "短轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMinor(),'f',9);
//    QString GetInvFlattening = "扁率 = " + QString::number(poDataset->GetSpatialRef()->GetInvFlattening(),'f',9);
//    double test[6];
//    poDataset->GetGeoTransform(test);
//    ui->plainTextEdit->clear();
//    ui->plainTextEdit->appendPlainText(Projected);
//    ui->plainTextEdit->appendPlainText(SemiMajor);
//    ui->plainTextEdit->appendPlainText(SemiMinor);
//    ui->plainTextEdit->appendPlainText(GetInvFlattening);
//    //upleft Coordinate
//    ui->plainTextEdit->appendPlainText("upperCoord = " + QString::number(test[0],'f',4));
//    ui->plainTextEdit->appendPlainText("leftCoord = " + QString::number(test[3],'f',4));
//    //pixel width and height
//    ui->plainTextEdit->appendPlainText("pixel width = " + QString::number(test[1],'f',4));
//    ui->plainTextEdit->appendPlainText("pixel height = " + QString::number(test[5],'f',4));
//    //变形信息
////    ui->plainTextEdit->appendPlainText(QString::number(test[2],'f',4));
////    ui->plainTextEdit->appendPlainText(QString::number(test[4],'f',4));

//    //查询value范围
//    GDALDataset::Bands poBands = poDataset->GetBands();
//    for(int i=1;i<poBands.size()+1;i++){
//        GDALRasterBand* poBand = poDataset->GetRasterBand(i);
//        ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最小值 : " + QString::number(getBandInfoMin(poBand).first()));
//        ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最大值 : " + QString::number(getBandInfoMin(poBand).last()));
//    }

*/
}


