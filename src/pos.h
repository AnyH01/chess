#ifndef CHESS_POS_H
#define CHESS_POS_H


/**
 * Class represents position by x and y.
**/
class Pos {
public:
    /**
     * @brief Represents x axis on the board.
     **/
    int x;

    /**
     * @brief Represents x axis on the board.
     **/
    char y;


    /**
     * @brief Constructor that sets position on default data.
     **/
    Pos();

    /**
     * @brief Constructor that sets position on entered data.
     * @param posX Represents x axis to be set from.
     * @param posY Represents y axis to be set from.
     **/
    Pos(int posX, char posY);

    /**
     * @brief Constructor that sets position on entered data.
     * @param posX Represents x axis to be set from.
     * @param posY Represents y axis to be set from.
     **/
    Pos(int posX, int posY);

    /**
     * @brief Method that sets position on entered data.
     * @param posX Represents x axis to be set from.
     * @param posY Represents y axis to be set from.
     **/
    void setPos(int posX, char posY);

    /**
     * @brief Method that sets position on entered position.
     * @param pos Position to be set from.
     **/
    void setPos(const Pos & pos);

    /**
     * @brief Method that sets x position on entered one.
     * @param posX Position x to be set from.
     **/
    void setX(int posX);

    /**
     * @brief Method that sets y position on entered one.
     * @param posY Position y to be set from.
     **/
    void setY(char posY);

    /**
     * @brief Method that gets x position.
     * @return Returns position x.
     **/
    int getX() const;

    /**
     * @brief Method that gets y position.
     * @return Returns position y.
     **/
    char getY() const;

    /**
     * @brief Method that gets x position on the board.
     * @return Returns position x on the board.
     **/
    int XInBoard() const;

    /**
     * @brief Method that gets y position on the board.
     * @return Returns position y on the board.
     **/
    int YInBoard() const;

    /**
     * @brief Operator that compares two positions.
     * @param pos Position to compare with.
     * @return Returns true if the positions are equal, false otherwise.
     **/
    bool operator == (const Pos & pos) const;

    /**
     * @brief Operator that compares two positions.
     * @param pos Position to compare with.
     * @return Returns true if the positions are not equal, false otherwise.
     **/
    bool operator != (const Pos & pos) const;
};

#endif //CHESS_POS_H
