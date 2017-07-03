# NEAT Properties

The NEAT policy system is based around the notion of NEAT properties. NEAT properties are essentially `key|value` tuples describing attributes used by the components of the NEAT Policy Manager. NEAT properties are used to express attributes describing the local host and the attached networks, user requirements, or constraints imposed by policies. Examples include interface names, types, supported protocols and parameters, or topology metrics (e.g., available bandwidth).

Each property has a `key` string and `value`. Currently property values can be

  1. a **single** boolean, integer, float or string value, e.g., `2`, `true`, or `"TCP"`. 
  2. a **set** of values: `[100, 200, 300, "foo"]`. 
  3. a numeric **range**: `{"start":1, "end":10}`.
  4. **ANY** value: `null`.

Each property is further associated with a `precedence` which identifies the "importance" of the property. Specifically, the precedence indicates if the property may be modified by the Policy Manager logic or if it is immutable. Currently two property precedence levels are defined in order of decreasing priority:

+ `[immutable]` (precedence **2**) these are mandatory properties whose value cannot be changed.
+ `(requested)` (precedence **1**) these are optional properties whose value may be overwritten. A mismatch of such properties will result in a penalty in the ranking within the PM. Such penalties are recorded as the `score` of the property.

The property's numeric `score` attribute is used to indicate the weight of the property with respect to other properties. Whenever two properties are compared and match the score of the result is the sum of the individual scores. As a consequence the PM can use the score to determine the most suitable NEAT connection `candidate` for a given request.

In the sequel we use the following shorthand notation: we separate the property key/value pair by the `|` character and indicate the property's precedence by the bracket types shown above. We append the score to the brackets and omit it if zero. For example

+  `[transport|TCP]+2`: the transport protocol *must* be "TCP"
+   `(MTU|1500,2000,9000)`: one of the specified MTU values *should* be chosen if possible
+   `(capacity|10-1000)+1`: the interface capacity should be within the numeric range specified by the integers

### Property Operators

1. Comparison: `p1 == P2`
    
    Any two NEAT properties are considered equal if their keys are identical and the intersection of their values is a non-empty set. Precedence and scores are ignored when testing for equality. A comparison - or **match** - of two properties yields a boolean result. 

    For instance, the operation `[transport|TCP]+1 == (transport|TCP)+3` yields true. Set and range value attributes are also considered equal if their values overlap, i.e., the expressions `[transport|TCP,UDP,MPTCP] == [transport|TCP]`, or `[latency|1-100]==[latency|55]` both return true.


2. Update: `p1 <= p2`

    In the lookup workflow in the PM, properties from various sources will be compared and potentially *updated*. Updates are the mechanism used to filter candidates which violate policies or contradict information stored in the CIB. Essentially, an update is successful if the property value of the involved properties do not contradict each other.     
    
    More specifically we use the following rules: a property may only be updated by another property with the same key. A property's value may **only** be updated by another property whose precedence is greater or equal than itself -- in which case it inherits the precedence of the updating property -- and if both properties are not immutable (highest precedence). A property update succeeds if the ranges of the associated properties overlap -- the resulting updated property will contain the intersection of the two ranges. Otherwise, if the above conditions are not satisfied, the update will fail. If the property is part of a PropertyArray a failed property update will invalidate the *entire* associated candidate. 

    As an example, if the immutable property `[transport|TCP]+2` is requested by an application and this property clashes with the property `[transport|UDP]` in a certain connection candidate, the candidate will be discarded.

  


## JSON Encoding:

The Policy Manager uses JSON to represent NEAT Properties. As an example, the property `[transport|TCP, SCTP]+3` is encoded as follows:

    "transport": {
       "value": ["TCP", "SCTP"],
       "precedence": 2,
       "score": 3
    }

The property `(latency|1-100)` is encoded as:

    "latency": {
       "value": {"start":1, "end":10}
    }

If a property attribute is omitted, the following default values will be used: `"value": null`, `"precedence": 2`, `"score": 0`, `"evaluated": false`.


### NEAT Property Arrays

A NEAT *PropertyArray* is a simple object containing a set of NEAT properties. These objects are used to represent applications *requests* received through the NEAT API as well as the connection *candidates* generated by the PM as the request traverses the PM logic.
 

A exemplary PropertyArray containing multiple properties looks as follows:

```
{
    "remote_ip": {"precedence": 2,"value": "10.54.1.23"}, 
    "port": {"precedence": 2, "value": 8080}, 
    "transport": {"value": "reliable"}, 
    "MTU": {"value": [1500, 9000]}, 
    "low_latency": {"precedence": 1, "value": true}
}
```

#TODO

If a candidate includes` immutable` properties with undefined scores the NEAT logic is responsible to ensure that these are can be fulfilled (an example of such a property would be security).