# JSON format example
```
{
    "settings": {
        "vertex_data_type": <default>,
        "edge_data_type": <default> 
    }
    "vertices": {
        {
            "id": string,
            "data": {
            }
        },
        ...
    },
    "edges": {
        {
            "id": string,
            "source": <vertex id>,
            "destination": <vertex id>,
            "data": {
            }
        }
    }
}
```