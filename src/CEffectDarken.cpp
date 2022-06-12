#include "CEffectDarken.hpp"
#include <vector>

std::shared_ptr<CImage> CEffectDarken::applyEffect(std::shared_ptr<CImage> image)
{
    unsigned int value = CEffect::getValue();
    std::vector<std::vector<double>> imageMatrix = image->getGrayscaleImage();
    std::vector<std::vector<double>> effectMatrix;
    for (size_t i = 0; i < imageMatrix.size(); i++)
    {
        std::vector<double> v1;
        for (size_t j = 0; j < imageMatrix[i].size(); j++)
        {
            if (imageMatrix[i][j] + value <= 255)
                v1.push_back(imageMatrix[i][j] + value);
            else
                v1.push_back(255);
        }
        effectMatrix.push_back(v1);
    }
    image->updateImage(effectMatrix);
    return image;
}