# fundamental_ranger
constexpr fundamental iterator and foreach for fundamental types

***
## range
```c++
blowin::rangers::range(0, table_widget->rowCount(), 
  [&table_widget,  collumn = 4, name = server_name->text()] (const int i) 
{
  const auto item = table_widget->item(i, collumn);
  if (item != nullptr && item->text() == name)
    table_widget->removeRow(i);
});
```

## fundamental_ranger
Fundamental ranger with STL algorithms 
```c++
blowin::rangers::fundamental_ranger<int> iranger(0, last_el_count);
const auto find_val = std::find_if(iranger.cbegin(), iranger.cend(), 
 [table_widget, &server_name, name_collumn_index = 3](const int i){
		return (table_widget->item(i) == server_name);
 });
if(find_val != iranger.cend())
	return;
```
