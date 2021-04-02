#include <iostream>
#include <fstream>
#include <cmath>

int main()
{

    std::fstream file_out;
    std::string filename="MyFile.txt";
    double ar_cur[50]{0};
    double ar_nx[50]{0};
    double ar_fin[50]{0};
    int k=0;

    for (int i=0;i<50;i++)
    {

        ar_cur[i]=std::sqrt(std::exp(-(i-2)*(i-2)));

    }
    ar_cur[49]=0;
    for (int t=1;t<100;t++)
    {

file_out.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
//        sprintf(filename,"out_%03d.txt",t);
        for (int v=-5;v<6;v++)
        {

            double G=std::abs(v*0.1);
            if (v>0)
            {

                for (int j=1;j<50;j++)
                {

                    ar_nx[j]=ar_cur[j]-G*(ar_cur[j]-ar_cur[j-1]);
                    ar_fin[j]+=ar_nx[j];

                }
                ar_fin[0]=ar_nx[0]=0;

            }
            if (v<0)
            {

                for (int j=1;j<49;j++)
                {

                    ar_nx[j]=ar_cur[j+1]-G*(ar_cur[j+1]-ar_cur[j]);
                    ar_fin[j]+=ar_nx[j];

                }
                ar_fin[49]=ar_nx[49]=0;

            }
            if (v==0)
            {

                for (int j=0;j<50;j++)
                {

                    ar_nx[j]=ar_cur[j];
                    ar_fin[j]+=ar_nx[j];

                }

            }

        }
        for (int i=0;i<50;i++)
        {
                file_out << k << '\t' << std::abs(ar_fin[i]) << std::endl;
                ar_fin[i] = 0;
            k++;

        }
        file_out<<" "<<std::endl;
        k=0;
        for (int i=0;i<50;i++)
        {

            ar_cur[i]=ar_nx[i];

        }
        file_out.close();
    }
    return 0;

}
