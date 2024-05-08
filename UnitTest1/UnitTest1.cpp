#include "pch.h"
#include "CppUnitTest.h"
#include "../AVLtree/main.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLTreeTests
{
	TEST_CLASS(AVLTreeTests)
	{
	public:
        TEST_METHOD(TestEmptyTree)
        {
            Node* root = nullptr;

            Assert::IsNull(root);

            root = deleteNode(root, 10);

            Assert::IsNull(root);

            root = insert(root, 20);

            Assert::IsNotNull(root);
            Assert::AreEqual(20, root->key);
            Assert::IsNull(root->left);
            Assert::IsNull(root->right);
        }


        TEST_METHOD(TestMinValueNode) {
            // Ñòâîğşºìî òåñòîâå äåğåâî
            Node* root = newNode(10);
            root->right = newNode(20);
            root->right->right = newNode(30);
            root->left = newNode(5);
            root->left->left = newNode(2);

            // Îòğèìóºìî íàéìåíøèé âóçîë
            Node* minNode = minValueNode(root);

            // Ïåğåâ³ğÿºìî ğåçóëüòàò
            Assert::IsNotNull(minNode);
            Assert::AreEqual(2, minNode->key);
        }



		TEST_METHOD(TestDeletionRoot)
		{
			Node* root = nullptr;
			root = insert(root, 10);
			root = insert(root, 20);
			root = insert(root, 30);
			root = insert(root, 40);
			root = insert(root, 50);
			root = insert(root, 60);

			root = deleteNode(root, 30);
			Assert::IsNotNull(root);
			Assert::AreEqual(40, root->key);
			Assert::AreEqual(20, root->left->key);
			Assert::AreEqual(50, root->right->key);
			Assert::AreEqual(60, root->right->right->key);
		}

	};
}
