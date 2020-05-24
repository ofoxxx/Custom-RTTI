CustomRTTI
==========
Testing custom RTTI variants

# Preamble
It is popular question about writing custom RTTI in C++ as it probably can reduce program's size and increase it's speed...
Such a magic I would raither explain by there is definitly something wrong with code/architecture but let's try to measure. 

# dynamic_cast
It's external to types i.e. do not require their modification - that's big plus. Types should be polymorphic.
(~0.008 ms*)

# Custom imitation
You should add types identification, relations and comparition mechanic. This addon can be significant modificacion of your types.
(~0.002 ms*)

# Visitor
No additional types id or data. You should add just one virtual member function per class in derivation. 
Due polimorphic dispatch the desired(real) type is given to Visitor. We can obtain it as casted.
(~0.0005 ms*)

Conslusion
==========
dynamic_cast is slower 5x-10x than custom alternatives but it does not require your types modification. And this combination of 
generality vs speed is OK. You should need rare type downcast otherwise your architecture 'smels'.
Visitor cast is the fastest and has the lowest impact on your types. If you really need custom cast Visitor is the best alternative to use.
