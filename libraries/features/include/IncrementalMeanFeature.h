////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     IncrementalMeanFeature.h (features)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Feature.h"
#include "BufferedFeature.h"
#include "CoordinateList.h"
#include "Model.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace features
{
    /// <summary>
    /// A feature that takes a vector input and returns its mean over some window of time.
    /// This feature is computed incrementally, so it takes \f$O(1)\f$ time instead of \f$O(n)\f$ time.
    /// </summary>
    class IncrementalMeanFeature : public BufferedFeature
    {
    public:
        /// <summary> Constructor </summary>
        /// <param name="inputFeature"> The feature to take the mean of </param>
        /// <param name="windowSize"> The number of samples of history to use in computing the mean </param>
        IncrementalMeanFeature(Feature* inputFeature, size_t windowSize);

        /// <summary> Constructor </summary>
        /// <param name="id"> The id to use for this feature </param>
        /// <param name="inputFeature"> The feature to take the mean of </param>
        /// <param name="windowSize"> The number of samples of history to use in computing the mean </param>
        IncrementalMeanFeature(const std::string& id, Feature* inputFeature, size_t windowSize);

        /// <summary> Creates an `IncrementalMeanFeature` from a vector of strings </summary>
        ///
        /// <param name="params"> The strings describing the parameters </params> 
        /// <param name="previousFeatures"> The map of existing features available as inputs. </params> 
        static std::unique_ptr<Feature> Create(std::vector<std::string> params, Feature::FeatureMap& previousFeatures);

        virtual std::string FeatureType() const override { return feature_name; }
        static constexpr const char* feature_name = "IncrementalMean";

    protected:
        virtual std::vector<double> ComputeOutput() const override;
        virtual layers::CoordinateList AddToModel(layers::Model& model, const std::unordered_map<const Feature*, layers::CoordinateList>& featureOutputs) const override;

    private:
        mutable std::vector<double> _runningSum;
    };
}
