////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     ConstantNode.tcc (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary> model namespace </summary>
namespace model
{
    // Constructor for a scalar constant

    // superclass (Node) constructor takes two array arguments: inputs and outputs. These are pointers to our local InputPort and OutputPort storage.
    template <typename ValueType>
    ConstantNode<ValueType>::ConstantNode(ValueType value) : Node({}, { &_output }), _output(this, 1), _values({ value }){};

    // Constructor for a vector constant
    template <typename ValueType>
    ConstantNode<ValueType>::ConstantNode(const std::vector<ValueType>& values, bool) : Node({ &_output }), _output(this, values.size()), _values(values){};

    template <typename ValueType>
    void ConstantNode<ValueType>::Compute() const
    {
        _output.SetOutput(_values);
    }

    template <typename ValueType>
    void ConstantNode<ValueType>::Copy(Model& newModel, ModelTransformer& transformer) const
    {
        auto newNode = newModel.AddNode<ConstantNode<ValueType>>(_values[0]);
        transformer.MapPort(&_output, &(newNode->_output));
    }

    template <typename ValueType>
    void ConstantNode<ValueType>::Refine(Model& newModel, ModelTransformer& transformer) const
    {
        auto newNode = newModel.AddNode<ConstantNode<ValueType>>(_values[0]);
        transformer.MapPort(&_output, &(newNode->_output));
    }
}
