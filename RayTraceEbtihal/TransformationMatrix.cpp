#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = 0;
		}
	}
}

TransformationMatrix TransformationMatrix::GetCopy()
{
	TransformationMatrix result ;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{					
			result.mat[i][j] = mat[i][j];
		}
	}
	return result;
}

void TransformationMatrix::CopyFrom(TransformationMatrix m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = m.mat[i][j];
		}
	}
}

TransformationMatrix TransformationMatrix::GetInverse()
{
	TransformationMatrix a = GetCopy();

            double tem = 0, temp = 0, temp1 = 0, temp2 = 0, temp4 = 0, temp5 = 0;
            int n = 4, i = 0, j = 0, p = 0, q = 0;

            TransformationMatrix id;

            for (i = 0; i < n; i++)
            {
                id.mat[i][i] = 1;
            }

            for (i = 0; i < n; i++)
            {
                temp = a.mat[i][i];
                if (temp < 0)
                    temp = temp * (-1);
                p = i;
                for (j = i + 1; j < n; j++)
                {
                    if (a.mat[j][i] < 0)
                        tem = a.mat[j][i] * (-1);
                    else
                        tem = a.mat[j][i];
                    if (temp < 0)
                        temp = temp * (-1);
                    if (tem > temp)
                    {
                        p = j;
                        temp = a.mat[j][i];
                    }
                }

                for (j = 0; j < n; j++)
                {
                    temp1 = a.mat[i][j];
                    a.mat[i][j] = a.mat[p][j];
                    a.mat[p][j] = temp1;
                    temp2 = id.mat[i][j];
                    id.mat[i][j] = id.mat[p][j];
                    id.mat[p][j] = temp2;
                }

                temp4 = a.mat[i][i];
                for (j = 0; j < n; j++)
                {
                    a.mat[i][j] = (float)a.mat[i][j] / temp4;
                    id.mat[i][j] = (float)id.mat[i][j] / temp4;
                }

                for (q = 0; q < n; q++)
                {
                    if (q == i)
                        continue;
                    temp5 = a.mat[q][i];
                    for (j = 0; j < n; j++)
                    {
                        a.mat[q][j] = a.mat[q][j] - (temp5 * a.mat[i][j]);
                        id.mat[q][j] = id.mat[q][j] - (temp5 * id.mat[i][j]);
                    }
                }
            }

            return id;
}

TransformationMatrix TransformationMatrix::GetTranspose()
{
	TransformationMatrix result ;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.mat[i][j] = mat[j][i];
		}
	}

	return result;
}

TransformationMatrix TransformationMatrix::ScaleMatrix(float scalingFactor)
{
	return GetCopy();
}

TransformationMatrix operator  *(TransformationMatrix A, TransformationMatrix B)
{
	TransformationMatrix C ;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{                    
			for (int k = 0; k < 4; ++k)
			{
				C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
			}
		}
	}

	return C;
}