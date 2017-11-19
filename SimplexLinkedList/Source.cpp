#include <iostream>
#include <string>


struct tagList
{
	tagList() {}
	tagList(const std::string& s) : str(s) {} 

	std::string str{ "None" };
	tagList* next{ nullptr };
};

tagList* begin_node{ nullptr };
tagList* end_node{ nullptr };

void Add(const std::string& str)
{
	if( begin_node == nullptr )
	{
		begin_node = new tagList( str );
		end_node = begin_node;
	}
	else
	{
		tagList* new_node = new tagList( str );
		end_node->next = new_node;
		end_node = new_node;
	}
}


bool Remove(const std::string& str)
{
	if ( begin_node != nullptr && begin_node->str == str )
	{
		if (begin_node->next != nullptr )
		{
			tagList* next_node = begin_node->next;
			delete begin_node;
			begin_node = next_node;
		}
		else
		{
			delete begin_node;
			begin_node = nullptr;
		}

		return true;
	}

	tagList* current_node = begin_node;

	while ( current_node->next != nullptr )
	{
		if ( current_node->next->str == str )
		{
			tagList* delete_node = current_node->next;
			current_node->next = current_node->next->next;
			delete delete_node;

			return true;
		}

		current_node = current_node->next;
	}
	
	return false;
}


void RemoveAll()
{
	tagList* current_node = begin_node;

	while ( current_node != nullptr )
	{
		tagList* delete_node = current_node->next;
		delete current_node;
		current_node = delete_node;
	}

	begin_node = nullptr;
	end_node = nullptr;

	printf( "Clear!\n" );
}

void ShowData()
{
	printf("=====================\n");

	tagList* current_node = begin_node;
	while ( current_node != nullptr )
	{
		printf( "%s\n", current_node->str.c_str() );

		current_node = current_node->next;
	}

	printf( "=====================\n" );
}

int main()
{
	Add("Harmony");
	Add( "Hooon_1" );
	Add( "Hooon_2" );
	Add( "Hooon_3" );
	Add( "Hooon_4" );
	Add( "Hooon_5" );

	Remove( "Harmony" );
	Remove("Hooon_1");

	ShowData();
	RemoveAll();
	ShowData();

	return 0;
}