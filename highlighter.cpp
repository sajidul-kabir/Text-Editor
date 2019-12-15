
#include "highlighter.h"
#include <QColor>



Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QColor("#DDA0DD"));
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bdelete\\b"), QStringLiteral("\\bif\\b"),
        QStringLiteral("\\bbool\\b"), QStringLiteral("\\bdo\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bdouble\\b"), QStringLiteral("\\blong\\b"),
        QStringLiteral("\\bcase\\b"), QStringLiteral("\\belse\\b"), QStringLiteral("\\bnamespace\\b"),
        QStringLiteral("\\bcatch\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bnew\\b"),
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bfalse\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bclass\\b"), QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bprivate\\b"),
        QStringLiteral("\\bconst\\b"), QStringLiteral("\\bfor\\b"), QStringLiteral("\\bprotected\\b"),
        QStringLiteral("\\bcontinue\\b"), QStringLiteral("\\bfriend\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bdefault\\b"), QStringLiteral("\\bgoto\\b"), QStringLiteral("\\bregister\\b"),
        QStringLiteral("\\breturn\\b"), QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bsizeof\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\bswitch\\b"), QStringLiteral("\\btemplate\\b"), QStringLiteral("\\bthis\\b"),
        QStringLiteral("\\bthrow\\b"), QStringLiteral("\\btrue\\b"), QStringLiteral("\\btypedef\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\busing\\b"),
        QStringLiteral("\\bvirtual\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bwhile\\b"),
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);

    }



    /*classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);*/



    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::gray);



    quotationFormat.setForeground(QColor("#66FF66"));
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);



    //functionFormat.setFontItalic(true);
    functionFormat.setFontWeight(QFont::Bold);
    functionFormat.setForeground(QColor("#9999FF"));
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);



    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));


    includeformat.setFontWeight(QFont::Bold);
    includeformat.setForeground(QColor("#FF9933"));
    rule.pattern = QRegularExpression(QStringLiteral("\\#[A-Za-z]+\\b"));
    rule.format=includeformat;
    highlightingRules.append(rule);



    headerfileformat.setFontWeight(QFont::Bold);
    headerfileformat.setForeground(QColor("#FF9933"));
    rule.pattern = QRegularExpression(QStringLiteral("\\<.*\\>"));
    rule.format=headerfileformat;
    highlightingRules.append(rule);
}


void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }


    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
