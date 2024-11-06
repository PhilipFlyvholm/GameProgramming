namespace MyEngine {
	static glm::vec2 DeserializeVector2(rapidjson::Value& vectorData) {
		assert(vectorData.IsArray() && "Trying to deserialize a vector from non-vector json value");
		assert(vectorData.Size() == 2 && "Trying to deserialize a vector from vector json value that doesn't have 2 elements");

		glm::vec2 ret{};
		for (int i = 0; i < vectorData.Size(); ++i)
			ret[i] = vectorData[i].GetFloat();

		return ret;
	}
}