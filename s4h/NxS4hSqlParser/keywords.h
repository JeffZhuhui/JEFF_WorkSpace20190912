//
// Created by jeff on 2019/12/6.
//
/*  USAGE:
#define FORMAT(A,B) A,
#include "keywords.h"
#undef  FORMAT(A,B)
 
#define FORMAT(A,B) ,{A, B}
#include "keywords.h"
#undef  FORMAT(A,B)
 * */
FORMAT(ABS, "ABS" )
FORMAT(ABSOLUTE, "ABSOLUTE" )
FORMAT(ACTION, "ACTION" )
FORMAT(ADD, "ADD" )
FORMAT(AFTER, "AFTER" )
FORMAT(ALL, "ALL" )
FORMAT(ALLOCATE, "ALLOCATE" )
FORMAT(ALTER, "ALTER" )
FORMAT(AND, "AND" )
FORMAT(ANY, "ANY" )
FORMAT(ARE, "ARE" )
FORMAT(AS, "AS" )
FORMAT(ASC, "ASC" )
FORMAT(ASSERTION, "ASSERTION" )
FORMAT(AT, "AT" )
FORMAT(ATION, "ATION" )
FORMAT(AUTHORI, "AUTHORI" )
FORMAT(AVG, "AVG" )
FORMAT(BEGIN, "BEGIN" )
FORMAT(BETWEEN, "BETWEEN" )
FORMAT(BIGINT, "BIGINT" )
FORMAT(BINARY, "BINARY" )
FORMAT(BLOB, "BLOB" )
FORMAT(BOTH, "BOTH" )
FORMAT(BY, "BY" )
FORMAT(CACHE, "CACHE" )
FORMAT(CALL, "CALL" )
FORMAT(CASCADE, "CASCADE" )
FORMAT(CASE, "CASE" )
FORMAT(CAST, "CAST" )
FORMAT(CATALOG, "CATALOG" )
FORMAT(CEILING, "CEILING" )
FORMAT(CHAR, "CHAR" )
FORMAT(CHARACTER, "CHARACTER" )
FORMAT(CHARACTER_LENGTH, "CHARACTER_LENGTH" )
FORMAT(CHAR_LENGTH, "CHAR_LENGTH" )
FORMAT(CHECK, "CHECK" )
FORMAT(CLOB, "CLOB" )
FORMAT(CLOSE, "CLOSE" )
FORMAT(CLUSTER, "CLUSTER" )
FORMAT(COALESCE, "COALESCE" )
FORMAT(COLLATE, "COLLATE" )
FORMAT(COLLATION, "COLLATION" )
FORMAT(COLUMN, "COLUMN" )
FORMAT(COMMENT, "COMMENT" )
FORMAT(COMMIT, "COMMIT" )
FORMAT(CONNECT, "CONNECT" )
FORMAT(CONNECTION, "CONNECTION" )
FORMAT(CONSTRAINT, "CONSTRAINT" )
FORMAT(CONSTRAINTS, "CONSTRAINTS" )
FORMAT(CONTINUE, "CONTINUE" )
FORMAT(CONVERT, "CONVERT" )
FORMAT(CORRESPONDING, "CORRESPONDING" )
FORMAT(COUNT, "COUNT" )
FORMAT(CREATE, "CREATE" )
FORMAT(CROSS, "CROSS" )
FORMAT(CURRENT, "CURRENT" )
FORMAT(CURRENT_DATE, "CURRENT_DATE" )
FORMAT(CURRENT_TIME, "CURRENT_TIME" )
FORMAT(CURRENT_TIMESTAMP, "CURRENT_TIMESTAMP" )
FORMAT(CURSOR, "CURSOR" )
FORMAT(DATABASE, "DATABASE" )
FORMAT(DATALINK, "DATALINK" )
FORMAT(DATE, "DATE" )
FORMAT(DAY, "DAY" )
FORMAT(DEALLOCATE, "DEALLOCATE" )
FORMAT(DEC, "DEC" )
FORMAT(DECIMAL, "DECIMAL" )
FORMAT(DECLARE, "DECLARE" )
FORMAT(DEFAULT, "DEFAULT" )
FORMAT(DEFERRABLE, "DEFERRABLE" )
FORMAT(DEFERRED, "DEFERRED" )
FORMAT(DELETE, "DELETE" )
FORMAT(DESC, "DESC" )
FORMAT(DESCRIBE, "DESCRIBE" )
FORMAT(DESCRIPTOR, "DESCRIPTOR" )
FORMAT(DIAGNOSTICS, "DIAGNOSTICS" )
FORMAT(DISABLE, "DISABLE" )
FORMAT(DISCONNECT, "DISCONNECT" )
FORMAT(DISTINCT, "DISTINCT" )
FORMAT(DO, "DO" )
FORMAT(DOMAIN, "DOMAIN" )
FORMAT(DOUBLE, "DOUBLE" )
FORMAT(DROP, "DROP" )
FORMAT(E, "E" )
FORMAT(ELSE, "ELSE" )
FORMAT(ENABLE, "ENABLE" )
FORMAT(END, "END" )
FORMAT(ESCAPE, "ESCAPE" )
FORMAT(EXCEPT, "EXCEPT" )
FORMAT(EXCEPTION, "EXCEPTION" )
FORMAT(EXCLUSIVE, "EXCLUSIVE" )
FORMAT(EXECUTE, "EXECUTE" )
FORMAT(EXISTS, "EXISTS" )
FORMAT(EXP, "EXP" )
FORMAT(EXPLAIN, "EXPLAIN" )
FORMAT(EXTERNAL, "EXTERNAL" )
FORMAT(EXTRACT, "EXTRACT" )
FORMAT(FALSE, "FALSE" )
FORMAT(FETCH, "FETCH" )
FORMAT(FIRST, "FIRST" )
FORMAT(FLOAT, "FLOAT" )
FORMAT(FLOOR, "FLOOR" )
FORMAT(FOR, "FOR" )
FORMAT(FOREIGN, "FOREIGN" )
FORMAT(FOUND, "FOUND" )
FORMAT(FROM, "FROM" )
FORMAT(FULL, "FULL" )
FORMAT(FUNCTION, "FUNCTION" )
FORMAT(GET, "GET" )
FORMAT(GLOBAL, "GLOBAL" )
FORMAT(GO, "GO" )
FORMAT(GOTO, "GOTO" )
FORMAT(GRANT, "GRANT" )
FORMAT(GROUP, "GROUP" )
FORMAT(GROUPING, "GROUPING" )
FORMAT(HAVING, "HAVING" )
FORMAT(HOUR, "HOUR" )
FORMAT(IDENTITY, "IDENTITY" )
FORMAT(IF, "IF" )
FORMAT(IMMEDIATE, "IMMEDIATE" )
FORMAT(IMPORT, "IMPORT" )
FORMAT(IN, "IN" )
FORMAT(INDEX, "INDEX" )
FORMAT(INDICATOR, "INDICATOR" )
FORMAT(INITIALLY, "INITIALLY" )
FORMAT(INNER, "INNER" )
FORMAT(INOUT, "INOUT" )
FORMAT(INPUT, "INPUT" )
FORMAT(INSENSITIVE, "INSENSITIVE" )
FORMAT(INSERT, "INSERT" )
FORMAT(INT, "INT" )
FORMAT(INTEGER, "INTEGER" )
FORMAT(INTERSECT, "INTERSECT" )
FORMAT(INTERVAL, "INTERVAL" )
FORMAT(INTO, "INTO" )
FORMAT(IS, "IS" )
FORMAT(ISOLATION, "ISOLATION" )
FORMAT(JOIN, "JOIN" )
FORMAT(KEY, "KEY" )
FORMAT(LABEL, "LABEL" )
FORMAT(LANGUAGE, "LANGUAGE" )
FORMAT(LAST, "LAST" )
FORMAT(LEADING, "LEADING" )
FORMAT(LEFT, "LEFT" )
FORMAT(LENGTH, "LENGTH" )
FORMAT(LEVEL, "LEVEL" )
FORMAT(LIKE, "LIKE" )
FORMAT(LIMIT, "LIMIT" )
FORMAT(LN, "LN" )
FORMAT(LOCAL, "LOCAL" )
FORMAT(LOCK, "LOCK" )
FORMAT(LOWER, "LOWER" )
FORMAT(MAP, "MAP" )
FORMAT(MATCH, "MATCH" )
FORMAT(MAX, "MAX" )
FORMAT(MERGE, "MERGE" )
FORMAT(MIN, "MIN" )
FORMAT(MINUTE, "MINUTE" )
FORMAT(MOD, "MOD" )
FORMAT(MODE, "MODE" )
FORMAT(MODULE, "MODULE" )
FORMAT(MONTH, "MONTH" )
FORMAT(NAMES, "NAMES" )
FORMAT(NATIONAL, "NATIONAL" )
FORMAT(NATURAL, "NATURAL" )
FORMAT(NCHAR, "NCHAR" )
FORMAT(NCLOB, "NCLOB" )
FORMAT(NEXT, "NEXT" )
FORMAT(NO, "NO" )
FORMAT(NOT, "NOT" )
//FORMAT(NULL, "NULL" )
FORMAT(NULLIF, "NULLIF" )
FORMAT(NUMERIC, "NUMERIC" )
FORMAT(NVARCHAR, "NVARCHAR" )
FORMAT(OCTET_LENGTH, "OCTET_LENGTH" )
FORMAT(OF, "OF" )
FORMAT(OFF, "OFF" )
FORMAT(ON, "ON" )
FORMAT(ONE, "ONE" )
FORMAT(ONE_HOUR, "ONE_HOUR" )
FORMAT(ONE_MINUTE, "ONE_MINUTE" )
FORMAT(ONLY, "ONLY" )
FORMAT(OPEN, "OPEN" )
FORMAT(OPTION, "OPTION" )
FORMAT(OR, "OR" )
FORMAT(ORDER, "ORDER" )
FORMAT(OUT, "OUT" )
FORMAT(OUTER, "OUTER" )
FORMAT(OUTPUT, "OUTPUT" )
FORMAT(OVERLAPS, "OVERLAPS" )
FORMAT(PAD, "PAD" )
FORMAT(PARTIAL, "PARTIAL" )
FORMAT(PARTITION, "PARTITION" )
FORMAT(PASSWORD, "PASSWORD" )
FORMAT(PERCENTILE_CONT, "PERCENTILE_CONT" )
FORMAT(PERCENTILE_DISC, "PERCENTILE_DISC" )
FORMAT(POSITION, "POSITION" )
FORMAT(POWER, "POWER" )
FORMAT(PRECISION, "PRECISION" )
FORMAT(PREPARE, "PREPARE" )
FORMAT(PRESERVE, "PRESERVE" )
FORMAT(PRIMARY, "PRIMARY" )
FORMAT(PRIOR, "PRIOR" )
FORMAT(PRIVILEGES, "PRIVILEGES" )
FORMAT(PROCEDURE, "PROCEDURE" )
FORMAT(PROGRAM, "PROGRAM" )
FORMAT(PUBLIC, "PUBLIC" )
FORMAT(REAL, "REAL" )
FORMAT(REFERENCES, "REFERENCES" )
FORMAT(RELATIVE, "RELATIVE" )
FORMAT(RELEASE, "RELEASE" )
FORMAT(RENAME, "RENAME" )
FORMAT(REPLACE, "REPLACE" )
FORMAT(RESET, "RESET" )
FORMAT(RESTRICT, "RESTRICT" )
FORMAT(RETURN, "RETURN" )
FORMAT(RETURNS, "RETURNS" )
FORMAT(REVOKE, "REVOKE" )
FORMAT(RIGHT, "RIGHT" )
FORMAT(ROLLBACK, "ROLLBACK" )
FORMAT(ROW, "ROW" )
FORMAT(ROWS, "ROWS" )
FORMAT(SCHEMA, "SCHEMA" )
FORMAT(SCROLL, "SCROLL" )
FORMAT(SECOND, "SECOND" )
FORMAT(SECTION, "SECTION" )
FORMAT(SELECT,"SELECT")
FORMAT(SEQUENCE, "SEQUENCE" )
FORMAT(SET, "SET" )
FORMAT(SHARE, "SHARE" )
FORMAT(SI, "SI" )
FORMAT(SIMPLE, "SIMPLE" )
FORMAT(SMALLINT, "SMALLINT" )
FORMAT(SOME, "SOME" )
FORMAT(SPACE, "SPACE" )
FORMAT(SQL, "SQL" )
FORMAT(SQLCODE, "SQLCODE" )
FORMAT(SQLERROR, "SQLERROR" )
FORMAT(SQLSTATE, "SQLSTATE" )
FORMAT(SQRT, "SQRT" )
FORMAT(STATISTICS, "STATISTICS" )
FORMAT(SUBSTRING, "SUBSTRING" )
FORMAT(SUM, "SUM" )
FORMAT(SYSTEM, "SYSTEM" )
FORMAT(SYSTEM_USER, "SYSTEM_USER" )
FORMAT(TABLE, "TABLE" )
FORMAT(TABLESPACE, "TABLESPACE" )
FORMAT(TEMPLATE, "TEMPLATE" )
FORMAT(TEMPORARY, "TEMPORARY" )
FORMAT(TEXT, "TEXT" )
FORMAT(THEN, "THEN" )
FORMAT(TIME, "TIME" )
FORMAT(TIMESTAMP, "TIMESTAMP" )
FORMAT(TO, "TO" )
FORMAT(TRAILING, "TRAILING" )
FORMAT(TRANSACTION, "TRANSACTION" )
FORMAT(TRANSLATION, "TRANSLATION" )
FORMAT(TRIM, "TRIM" )
FORMAT(TRUE, "TRUE" )
FORMAT(TRUNCATE, "TRUNCATE" )
FORMAT(TYPE, "TYPE" )
FORMAT(UNION, "UNION" )
FORMAT(UNIQUE, "UNIQUE" )
FORMAT(UNKNOWN, "UNKNOWN" )
FORMAT(UPDATE, "UPDATE" )
FORMAT(UPPER, "UPPER" )
FORMAT(USAGE, "USAGE" )
FORMAT(USER, "USER" )
FORMAT(USING, "USING" )
FORMAT(VALUE, "VALUE" )
FORMAT(VALUES, "VALUES" )
FORMAT(VARBINARY, "VARBINARY" )
FORMAT(VARCHAR, "VARCHAR" )
FORMAT(VARYING, "VARYING" )
FORMAT(VIEW, "VIEW" )
FORMAT(VOLATILE, "VOLATILE" )
FORMAT(WHEN, "WHEN" )
FORMAT(WHENEVER, "WHENEVER" )
FORMAT(WHERE, "WHERE" )
FORMAT(WITH, "WITH" )
FORMAT(WORK, "WORK" )
FORMAT(WRITE, "WRITE" )
FORMAT(YEAR, "YEAR" )

FORMAT(TOP, "TOP" )
FORMAT(CONTAINS, "CONTAINS" )
FORMAT(FUZZY, "FUZZY" )
FORMAT(PARAMETERS, "PARAMETERS" )

/* this is data type keywords
BIGINT
BINARY
BLOB
CHAR
CLOB
DOUBLE
DATALINK
DATE
DECIMAL
FLOAT
INT
INTEGER
NCLOB
REAL
SMALLINT
TIME
TIMESTAMP
TEXT
VARBINARY
VARCHAR
 */