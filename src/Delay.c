/**
 * @brief 实现延时功能
 * 
 * @param 延时的ms
 */
void Delay( unsigned int a)		
{
	while(a>0)
	{unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		a--;
	}
}