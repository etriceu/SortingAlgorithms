#include <vector>
#include <algorithm>

namespace sort
{
	namespace
	{
		template <class T>
		void _merge(T *beg, T* mid, T *end)
		{
			T tmp[end-beg];
			T *a = beg, *b = mid, *c = tmp;
			
			for(; a < mid && b < end; c++)
				*c = *a < *b ? *(a++) : *(b++);

			while(a < mid)
				*(c++) = *(a++);
			
			while(b < end)
				*(c++) = *(b++);
			
			for(c = tmp; beg < end; c++, beg++)
				*beg = *c;
		}

		template <class T>
		void _heap(T *arr, int n, int i)
		{
			int l = i*2+1, r = l+1, m = i;
			
			if(l < n && arr[l] > arr[m])
				m = l;
			
			if(r < n && arr[r] > arr[m])
				m = r;
			
			if(m != i)
			{
				std::swap(arr[i], arr[m]);
				_heap(arr, n, m);
			}
		}

		template <class T>
		void _bucket(T *beg, std::vector<T> *b, std::vector<T> *e)
		{
			for(; b < e; b++)
			{
				for(T num : *b)
					*(beg++) = num;
				
				b->clear();
			}
		}

		template <class T>
		T* _quick(T *beg, T *last)
		{
			T pivot = *beg, *i = beg;
			for(T *it = beg+1; it <= last; it++)
				if(*it <= pivot)
					i++;
			
			std::swap(*i, *beg);
			for(T *a = beg, *b = last; a < i && b > i;)
			{
				for(; *a <= pivot; a++);
				for(; *b > pivot; b--);
				if(a < i && b > i)
					std::swap(*(a++), *(b--));
			}
			return i;
		}
	}
	
	template <class T>
	void bubble(T *beg, T *end)
	{
		for(T *a, *b, *it = beg; it < --end;)
			for(a = beg, b = beg+1, it = end; a < end; a++, b++)
				if(*a > *b)
				{
					std::swap(*a, *b);
					it = beg;
				}
	}

	template <class T>
	void selection(T *beg, T *end)
	{
		for(; beg < end; beg++)
		{
			T *min = beg;
			for(T *it = beg+1; it < end; it++)
				if(*it < *min)
					min = it;
			
			std::swap(*min, *beg);
		}
	}

	template <class T>
	void merge(T *beg, T *end)
	{
		if(beg == end-1)
			return;
			
		T *mid = beg+(end-beg)/2;
		merge(beg, mid);
		merge(mid, end);
		_merge(beg, mid, end);
	}

	template <class T>
	void insertion(T *beg, T *end)
	{
		for(T *it = beg+1; it < end; it++)
		{
			T tmp = *it, *b = it;
			for(T *a = it-1; *a > tmp && b > beg; a--, b--)
				*b = *a;
			
			*b = tmp;
		}
	}

	template <class C = uint8_t, class Iter, class T>
	void counting(Iter beg, Iter end, T max, T min = 0)
	{
		size_t size = std::max<size_t>(abs(max-min)+1, end-beg);
		C *count = new C[size]();

		for(Iter n = beg; n != end; n++)
			count[*n-min]++;

		for(size_t n = 0; n < size; n++)
			for(Iter m = beg+count[n]; m != beg; beg++)
				*beg = n+min;

		delete [] count;
	}

	template <class T>
	void heap(T *arr, int n)
	{
		int i;
		for(i = n/2-1; i >= 0; i--)
			_heap(arr, n, i);
		
		for(i = n-1; i >= 0; i--)
		{
			std::swap(arr[0], arr[i]);
			_heap(arr, i, 0);
		}
	}

	template <class T>
	void bucket(T *beg, T *end)
	{
		size_t size = 16;
		if constexpr (std::is_floating_point_v<T>)
			size = end-beg;
		
		std::vector <T> tmp[size];
		if constexpr(std::is_floating_point_v<T>)
		{
			for(T *it = beg; it < end; it++)
				tmp[int(size*(*it))].push_back(*it);
			
			for(auto &it : tmp)
				std::sort(it.begin(), it.end());
			
			_bucket(beg, tmp, tmp+size);
		}
		else
		{
			for(int n = 1; n < sizeof(T)*8; n *= 16)
			{
				for(T *it = beg; it < end; it++)
					tmp[(*it/n)%16].push_back(*it);
				
				_bucket(beg, tmp, tmp+size);
			}
		}
	}

	template <class T>
	void quick(T *beg, T *last)
	{
		if(beg >= last)
			return;
		
		T *p = _quick(beg, last);
		quick(beg, p-1);
		quick(p+1, last);
	}
};
