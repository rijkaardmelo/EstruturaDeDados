#include <gtest/gtest.h>

#include "ordenacao.h"

class TestOrdenacao : public ::testing::Test
{
protected:
    virtual void TearDown()
    {
        free(v);
    }

    virtual void SetUp()
    {
        v = (int *)malloc(tamanho * sizeof(int));

        for (int i = 0; i < tamanho; i++)
            v[i] = rand() % 1000;
    }

    int *v;
    int tamanho = 1000;
    int nTestes = 1;
};

void selectionSortTestInstance(int *v, int tamanho, bool inPlace)
{
    if (inPlace == true)
        selectionSortIP(v, tamanho);
    else
        selectionSortOP(&v, tamanho);

    for (int i = 0; i < tamanho - 1; i++)
        EXPECT_TRUE(v[i] <= v[i + 1]);
}

TEST_F(TestOrdenacao, SelectionSortOP)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        selectionSortTestInstance(v, tamanho, false);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, SelectionSortIP)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        selectionSortTestInstance(v, tamanho, true);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, BubbleSort)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        bubbleSort(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortOP)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortOP(&v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortIPV1)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortIPV1(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortIPV2)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortIPV2(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortIPV3)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortIPV3(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortIPV4)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortIPV4(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, InsertionSortIPV5)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        insertionSortIPV5(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, MergeSort)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        mergeSort(v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, QuickSort)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        quickSort(v, 0, tamanho - 1);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, QuickSortRP)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        quickSortRP(v, 0, tamanho - 1);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

TEST_F(TestOrdenacao, CountingSort)
{
    for (int i = 0; i < nTestes; i++)
    {
        SetUp();
        countingSort(&v, tamanho);

        for (int i = 0; i < tamanho - 1; i++)
            EXPECT_TRUE(v[i] <= v[i + 1]);

        if (i != nTestes - 1)
            TearDown();
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}