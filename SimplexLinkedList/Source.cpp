#include <iostream>
#include <string>
#include <crtdbg.h>

#pragma region "define node"
struct tagNode
{
	tagNode() { }
	tagNode( std::string&& n ) : name( std::move( n ) ) { }

	std::string name{"None"};
	tagNode* next{ nullptr };
};

tagNode* head_node = nullptr;
tagNode* tail_node = nullptr;
#pragma endregion

#pragma region "function list for simplex linked list"

size_t GetListCount()
{
	size_t list_count = 0;

	tagNode* current_node = head_node;

	while ( current_node->next != nullptr )
	{
		current_node= current_node->next;
		list_count++;
	}

	return list_count;
}

void Add( std::string n )
{
	tail_node->next = new tagNode( std::move( n ) );
	tail_node = tail_node->next;
}

tagNode* Find( std::string n )
{
	tagNode* current_node = head_node;

	while ( current_node->next != nullptr )
	{
		if ( current_node->next->name == n )
		{
			return current_node->next;
		}

		current_node = current_node->next;
	}

	return nullptr;
}

tagNode* Find( size_t index )
{
	size_t current_index = 0;
	tagNode* current_node = head_node;

	while ( current_node->next != nullptr )
	{
		if ( current_index == index )
		{
			return current_node->next;
		}

		current_node = current_node->next;
		current_index++;
	}

	return nullptr;
}

tagNode* ReverseFind( size_t index )
{
	size_t max_count = GetListCount();
	size_t loop_count = max_count - index - 1;
	size_t current_index = 0;

	tagNode* current_node = head_node;

	while (current_node->next != nullptr )
	{
		if ( current_index == loop_count )
		{
			return current_node->next;
		}

		current_node = current_node->next;
		current_index++;
	}

	return nullptr;
}

void Reverse()
{
	tagNode* current_node = head_node->next;
	tagNode* two_prev_node = nullptr;
	tagNode* prev_node = nullptr;

	if ( head_node->next != nullptr )
	{
		tail_node = head_node->next;
	}
	
	while ( current_node != nullptr )
	{
		if ( current_node->next == nullptr )
		{
			head_node->next = current_node;
		}

		two_prev_node = prev_node;
		prev_node = current_node;
		current_node = current_node->next;
		prev_node->next = two_prev_node;
	}
}

void Remove( std::string n)
{
	tagNode* current_node = head_node;

	while ( current_node->next != nullptr )
	{
		if ( current_node->next->name == n )
		{
			if ( current_node->next->next == nullptr )
			{
				tail_node = current_node;
			}

			tagNode* delete_node = current_node->next;
			current_node->next = current_node->next->next;
			delete delete_node;

			return;
		}

		current_node = current_node->next;
	}
}

void RemoveAll()
{
	std::cout << "===== RemoveAll =====" << std::endl;

	tagNode* current_node = head_node;

	while ( current_node->next != nullptr )
	{
		tagNode* delete_node = current_node->next;
		current_node->next = current_node->next->next;
		delete delete_node;
	}

	head_node->next = nullptr;
	tail_node = head_node;

	std::cout << "================" << std::endl;
}

void Show()
{
	std::cout << "===== Show =====" << std::endl;

	tagNode* current_node = head_node;

	while( current_node->next != nullptr )
	{
		std::cout << current_node->next->name << std::endl;
		current_node = current_node->next;
	}

	std::cout << "================" << std::endl;
}

void ShowNode ( tagNode* node)
{
	if ( node == nullptr )
	{
		return;
	}

	std::cout << node->name << std::endl;
}

#pragma endregion

int main()
{
#pragma region "Check memory leak"
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#pragma endregion

#pragma region "Allocate memory"
	head_node = new tagNode{};
	tail_node = head_node;
#pragma endregion

	Add( "1" );
	Add( "2" );
	Add( "3" );
	Add( "4" );
	Add( "5" );
	Show();

	ShowNode( Find( 3 ) );
	ShowNode( Find( "2" ) );
	ShowNode( ReverseFind( 2 ) );

	Reverse();
	Show();

	Remove("3");
	Remove("1");
	Show();

	RemoveAll();
	Show();

#pragma region "Release"
	RemoveAll();

	if (head_node != nullptr )
	{
		delete head_node;
		head_node = nullptr;
	}
#pragma endregion

	return 0;
}