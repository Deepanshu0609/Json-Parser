A basic JSON-Parser written in C++.

Follows the basic grammar of JSON.

**grammar followed **:

{

Object -> key(String) : Val(String | Number | Object | Array | Boolean | Null) | ',' 

Array -> [(String | Number | Boolean | Null | Object | Array)',']

}

**TO-DO**

Add validation for escape characters

Add validation for unicode
