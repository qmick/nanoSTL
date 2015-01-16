#ifndef _ALGO_HPP_
#define _ALGO_HPP_

template <typename T> 
void Swap(T &_Left, T &_Right)
{
	T _Val  = _Left;
	_Left   = _Right;
	_Right  = _Val;
}

template <typename T> 
T mid(T a, T b, T c)
{
	if(a < b)
		if(b < c)
			return b;
		else if(c < a)
			return a;
		else
			return c;
	else if(c > a)
		return a;
	else if(b > c)
		return b;
	else
		return c;
}

template <typename RanIt> 
void shiftDown(RanIt it_begin, RanIt it_end, int index)
{
	if(it_end - it_begin <= 1)
		return;
	int i = index;
	while(i <= std::distance(it_begin, it_end - 2) / 2)
	{
		if(std::distance(it_begin, it_end - 1) < 2 * i + 2)
		{
			if(*(it_begin + i) < *(it_begin + 2 * i + 1))
				 Swap(*(it_begin + i), *(it_begin + 2 * i + 1));
			 return;
		}
			 
		if(*(it_begin + 2 * i + 1) > *(it_begin + 2 * i + 2))
			if(*(it_begin + i) < *(it_begin + 2 * i + 1))
			{
				Swap(*(it_begin + i), *(it_begin + 2 * i + 1));
				i = 2 * i + 1;
			}
			else break;
		else if(*(it_begin + i) < *(it_begin + 2 * i + 2))
		{
			Swap(*(it_begin + i), *(it_begin + 2 * i + 2));
			i = 2 * i + 2;
		}
		else break;
	}
}

template <typename RanIt> 
void selectionSort(RanIt it_begin, RanIt it_end)
{
	RanIt i = it_begin;
	RanIt _ptr;
	bool flag;
	for(; i != it_end; i++)
	{
		_ptr = i;
		flag = false;
		for(RanIt j = i + 1; j != it_end; j++)
			if(*j < *_ptr)
			{
				_ptr = j;
				flag  = true;
			}
			if(flag)	
				Swap(*i, *_ptr);				
	}		
}

template <typename RanIt, typename Compare> 
void insertionSort(RanIt it_begin, RanIt it_end, const Compare &comp)
{
	typedef typename std::iterator_traits<RanIt>::value_type value_type;
	int i, j;
	value_type temp;
	
	for(i = 1; i <= std::distance(it_begin, it_end - 1); i++)
	{
		temp = *(it_begin + i);
		j = i - 1;
		if(comp(*(it_begin + i), *it_begin))
		{
			for(; j >= 0; j--)
				*(it_begin + j + 1) = *(it_begin + j);
			*it_begin = temp;
			continue;
		}
		while(j >= 0 && comp(temp, *(it_begin + j)))
		{
			*(it_begin + j + 1) = *(it_begin + j);
			j--;
		}
		*(it_begin + 1 + j) = temp;		
	}
}

template <typename RanIt> 
void insertionSort(RanIt it_begin, RanIt it_end)
{
	typedef typename std::iterator_traits<RanIt>::value_type value_type;
	int i, j;
	value_type temp;
	
	for(i = 1; i <= std::distance(it_begin, it_end - 1); i++)
	{
		temp = *(it_begin + i);
		j = i - 1;

		while(j >= 0 && *(it_begin + j) > temp)
		{
			*(it_begin + j + 1) = *(it_begin + j);
			j--;
		}
		*(it_begin + 1 + j) = temp;		
	}	
}

template <typename RanIt> 
void heapSort(RanIt it_begin, RanIt it_end)
{
	for(int i = std::distance(it_begin, it_end) / 2 - 1; i >= 0; i--)
		shiftDown(it_begin, it_end, i);
	
	RanIt _ptr = it_end - 1;
	while(_ptr != it_begin)
	{
		Swap(*_ptr, *it_begin);
		shiftDown(it_begin, _ptr, 0);
		_ptr--;
	}
}
		
template <typename RanIt, typename Compare>
void __qsort(RanIt it_begin, RanIt it_end, const Compare &comp)
{
	if(it_end - it_begin < 15)	return;

	typedef typename std::iterator_traits<RanIt>::value_type value_type;
	value_type iv = mid(*it_begin, 
						*(it_begin + (it_end - it_begin) / 2), 
						*(it_end - 1));

	RanIt _l_ite = it_begin;
	RanIt _r_ite = it_end;

	while(true)
	{
		while(comp(*_l_ite, iv))	_l_ite++;
		_r_ite--;
		while(comp(iv, *_r_ite))	_r_ite--;
		if(!(_l_ite < _r_ite))	break;
		Swap(*_l_ite, *_r_ite);
		_l_ite++;
	}

	__qsort(it_begin, _l_ite, comp);
	__qsort(_l_ite, it_end, comp);
}

template <typename RanIt, typename Compare>
void esort(RanIt it_begin, RanIt it_end, const Compare &comp)
{
	__qsort(it_begin, it_end, comp);
	insertionSort(it_begin, it_end, comp);
}

template <typename RanIt> 
void esort(RanIt it_begin, RanIt it_end)
{
	typedef typename std::iterator_traits<RanIt>::value_type value_type;

	__qsort(it_begin, it_end, std::less<value_type>());
	insertionSort(it_begin, it_end, std::less<value_type>());
}


#endif