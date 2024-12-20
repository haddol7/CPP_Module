#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "PmergeMe.hpp"

#define JACOPSTHAL(i) (((1 << ((i) + 1)) + ((i) % 2 == 0 ? 1 : -1)) / 3)

/*

first<value>	4	2	9	1	0	3	8	7
second<index>	0	1	2	3	4	5	6	7

first<value>	4	2	9	1	0	3	8	7
second<index>	4	2	7	1	0	3	6	5

*/

PmergeMe::PmergeMe(int argc, char *argv[])
{
	long	number;
	char	*end;

	if (argc < 2)
		throw (std::invalid_argument("Error"));
	for (int i = 1; i < argc; ++i)
	{	
		number = strtol(argv[i], &end, 10);
		if (number < 0 || *end != '\0' || static_cast<int>(number) != number)
			throw (std::invalid_argument("Error"));
		mArrayVector.push_back(number);
		mArrayList.push_back(number);
	}
}

void	PmergeMe::sort()
{
	sort_with_clock(mArrayVector);
	sort_with_clock(mArrayList);

	if (mArrayList.size() != mArrayVector.size() || !std::equal(mArrayList.begin(), mArrayList.end(), mArrayVector.begin()))
		throw (std::logic_error("Evaluate as KO.."));
		
	for (size_t i = 1; i < mArrayVector.size(); ++i)
	{
		if (mArrayVector[i - 1] > mArrayVector[i])
			throw (std::logic_error("Evaluate as KO.."));
	}
}

typedef	std::pair<int, size_t> 											t_pair_value_index;
typedef std::vector<t_pair_value_index>									t_vec_value_index;
typedef std::vector<std::pair<t_pair_value_index, t_pair_value_index> >	t_vec_main_sub_chain_index;
typedef std::list<t_pair_value_index>									t_list_value_index;
typedef std::list<std::pair<t_pair_value_index, t_pair_value_index> >	t_list_main_sub_chain_index;

static t_vec_value_index::iterator binary_search(t_vec_value_index &result, int value, size_t right)
{
	size_t	left = 0;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (result[mid].first < value)
			left = mid + 1;
		else
			right = mid;
	}
	return result.begin() + left;
}

static t_list_value_index::iterator binary_search(t_list_value_index &result, int value, size_t right)
{
	size_t	left = 0;
	t_list_value_index::iterator it;

	while (left < right)
	{
		it = result.begin();
		size_t mid = left + (right - left) / 2;
		std::advance(it, mid);
		if (it->first < value)
			left = mid + 1;
		else
			right = mid;
	}
	it = result.begin();
	std::advance(it, left);
	return (it);
}

static void	ford_johnson(t_vec_value_index &ary)
{
	size_t	size = ary.size();

	if (size <= 1)
		return ;
	else if (size == 2)
	{
		if (ary[0].first > ary[1].first)
			std::swap(ary[0].second, ary[1].second);
		return ;
	}
	t_vec_main_sub_chain_index	whole_chain;
	t_vec_value_index		main_chain;

	whole_chain.reserve(size / 2);
	main_chain.reserve(size / 2);
	//whole_chain = 메인 체인과 서브 체인
	//main_chain = 메인 체인만 들어감. 각 요소에는 원래 있던 index 위치를 들고 간다.
	for (size_t i = 0; i < size / 2; ++i)
	{
		if (ary[i * 2].first > ary[i * 2 + 1].first)
		{
			whole_chain.push_back(std::make_pair(std::make_pair(ary[i * 2].first, i * 2), std::make_pair(ary[i * 2 + 1].first, i * 2 + 1)));
			main_chain.push_back(std::make_pair(ary[i * 2].first, i));
		}
		else
		{
			whole_chain.push_back(std::make_pair(std::make_pair(ary[i * 2 + 1].first, i * 2 + 1), std::make_pair(ary[i * 2].first, i * 2)));
			main_chain.push_back(std::make_pair(ary[i * 2 + 1].first, i));
		}
	}

	//먼저 재귀적으로 들어가 메인 체인을 정렬하도록 한다.
	//함수 호출이 다 끝나면, main_chain에 있는 second 요소(index)는 정렬되었을 때 해당 요소가 위치할 index이다.
	ford_johnson(main_chain);
	t_vec_main_sub_chain_index	sorted_whole_chain;
	t_vec_value_index 		result;

	sorted_whole_chain.resize(size / 2);
	result.reserve(size);
	//sorted_whole_chain = 메인 체인이 정렬된 상태
	//result = 나머지 서브 체인을 jacobsthal 수열대로 넣을 배열
	for (size_t i = 0; i < size / 2; ++i)
		sorted_whole_chain[main_chain[i].second] = whole_chain[i];
	for (size_t i = 0; i < size / 2; ++i)
		result.push_back(sorted_whole_chain[i].first);
	bool 	loop = true;
	size_t	i = 2;
	size_t	k = 4;

	//첫번째 요소를 넣고 시작한다.
	result.insert(result.begin(), sorted_whole_chain[0].second);
	do
	{
		//jacobsthal 순서대로 subchain에 있는 요소를 insertion한다. 
		size_t	ford_i = std::min(static_cast<size_t>(JACOPSTHAL(i)), size / 2) - 1;
		if (ford_i == size / 2 - 1)
		{
			k = result.size();
			loop = false;
		}
		for (; ford_i >= static_cast<size_t>(JACOPSTHAL(i - 1)); --ford_i)
			result.insert(binary_search(result, sorted_whole_chain[ford_i].second.first, k - 1), sorted_whole_chain[ford_i].second);
		k *= 2;
		i++;
	} while (loop);
	//홀수는 체인에 없으므로, 마지막에 하나 넣어준다.
	if (size % 2 == 1)
		result.insert(binary_search(result, ary[size - 1].first, size - 1), ary[size - 1]);
	//이제 다 정렬된 요소의 순서를 집어 넣는다.
	for (size_t j = 0; j < size; ++j)
		ary[result[j].second].second = j;
}

static void	ford_johnson(t_list_value_index &ary)
{
	size_t	size = ary.size();

	if (size <= 1)
		return ;
	else if (size == 2)
	{
		if (ary.begin()->first > (--ary.end())->first)
			std::swap(ary.begin()->second, (--ary.end())->second);
		return ;
	}
	t_list_main_sub_chain_index		whole_chain;
	t_list_value_index				main_chain;
	t_list_value_index::iterator 	it;
	t_list_value_index::iterator 	it_odd;
	for (size_t i = 0; i < size / 2; ++i)
	{
		it = ary.begin();
		std::advance(it, i * 2);
		it_odd = it;
		std::advance(it_odd, 1);
		if (it->first > it_odd->first)
		{
			whole_chain.push_back(std::make_pair(std::make_pair(it->first, i * 2), std::make_pair(it_odd->first, i * 2 + 1)));
			main_chain.push_back(std::make_pair(it->first, i));
		}
		else
		{
			whole_chain.push_back(std::make_pair(std::make_pair(it_odd->first, i * 2 + 1), std::make_pair(it->first, i * 2)));
			main_chain.push_back(std::make_pair(it_odd->first, i));
		}
	}
	ford_johnson(main_chain);
	t_list_main_sub_chain_index				sorted_whole_chain;
	t_list_main_sub_chain_index::iterator	it_chain;
	t_list_main_sub_chain_index::iterator	it_whole_chain;
	t_list_value_index 						result;

	sorted_whole_chain.resize(size / 2);
	for (size_t i = 0; i < size / 2; ++i)
	{
		it = main_chain.begin();
		std::advance(it, i);
		it_chain = sorted_whole_chain.begin();
		std::advance(it_chain, it->second);
		it_whole_chain = whole_chain.begin();
		std::advance(it_whole_chain, i);
		*it_chain =  *it_whole_chain;
	}
	it_chain = sorted_whole_chain.begin();
	for (size_t i = 0; i < size / 2; ++i)
	{
		result.push_back(it_chain->first);
		std::advance(it_chain, 1);
	}
	bool 	loop = true;
	size_t	i = 2;
	size_t	k = 4;
	result.insert(result.begin(), sorted_whole_chain.begin()->second);
	do
	{
		size_t	ford_i = std::min(static_cast<size_t>(JACOPSTHAL(i)), size / 2) - 1;
		if (ford_i == size / 2 - 1)
		{
			k = result.size();
			loop = false;
		}
		for (; ford_i >= static_cast<size_t>(JACOPSTHAL(i - 1)); --ford_i)
		{
			it_chain = sorted_whole_chain.begin();
			std::advance(it_chain, ford_i);
			result.insert(binary_search(result, it_chain->second.first, k - 1), it_chain->second);
		}
		k *= 2;
		i++;
	} while (loop);
	if (size % 2 == 1)
		result.insert(binary_search(result, (--ary.end())->first, size - 1), *(--ary.end()));
	for (size_t j = 0; j < size; ++j)
	{
		it = result.begin();
		std::advance(it, j);
		it_odd = ary.begin();
		std::advance(it_odd, it->second);
		it_odd->second = j;
	}
}

void PmergeMe::sort_with_clock(std::vector<int> &ary)
{
	std::cout << "Before:\t" << std::flush;
	print_vector(ary);

	size_t				size = ary.size();
	clock_t 			start;
	clock_t				end;
	double				elapsed_us;

	start = clock();
	t_vec_value_index	ary_index;

	ary_index.reserve(size);
	for (size_t i = 0; i < size; ++i)
		ary_index.push_back(std::make_pair(ary[i], i));
	ford_johnson(ary_index);
	for (size_t i = 0; i < size; ++i)
		ary[ary_index[i].second] = ary_index[i].first;
    
	end = clock();
	elapsed_us = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "After:\t" << std::flush;
	print_vector(ary);
	std::cout << std::fixed << std::setprecision(0) << "Time to process a range of " << size << " elements with std::vector : " << elapsed_us << " us" << std::endl;
}

void PmergeMe::sort_with_clock(std::list<int> &ary)
{
	size_t				size = ary.size();
	clock_t 			start;
	clock_t				end;
	double				elapsed_us;

	start = clock();
	t_list_value_index			ary_index;
	std::list<int>::iterator	it = ary.begin();
	for (size_t i = 0; i < size; ++i)
	{
		ary_index.push_back(std::make_pair(*it, i));
		++it;
	}
	ford_johnson(ary_index);
	t_list_value_index::iterator	it_ary;
	for (size_t i = 0; i < size; ++i)
	{
		it = ary.begin();
		it_ary = ary_index.begin();
		std::advance(it_ary, i);
		std::advance(it, it_ary->second);

		*it = it_ary->first;
	}
	end = clock();
	elapsed_us = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << std::fixed << std::setprecision(0) << "Time to process a range of " << size << " elements with std::list   : " << elapsed_us << " us" << std::endl;
}

void PmergeMe::print_vector(std::vector<int> &ary)
{
	for (size_t i = 0; i < ary.size(); i++)
		std::cout << ary[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::print_vector(std::list<int> &ary)
{
	for (std::list<int>::iterator it = ary.begin(); it != ary.end();)
	{
		std::cout << *it << " ";
		std::advance(it, 1);
	}
	std::cout << std::endl;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& cpy)
{
	*this = cpy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs)
	{
		mArrayList = rhs.mArrayList;
		mArrayVector = rhs.mArrayVector;
	}
	return (*this);
}
