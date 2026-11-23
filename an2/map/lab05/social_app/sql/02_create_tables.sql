CREATE TABLE IF NOT EXISTS users (
    id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL
);

ALTER TABLE users
    ADD COLUMN IF NOT EXISTS email VARCHAR(255) DEFAULT '',
    ADD COLUMN IF NOT EXISTS birth_date VARCHAR(10) DEFAULT '',
    ADD COLUMN IF NOT EXISTS description TEXT DEFAULT '';

CREATE TABLE IF NOT EXISTS friendships (
    id1 BIGINT NOT NULL,
    id2 BIGINT NOT NULL,
    friends_from TIMESTAMP NOT NULL,

    CONSTRAINT friendships_pk PRIMARY KEY (id1, id2),
    CONSTRAINT friendships_user1_fk FOREIGN KEY (id1) REFERENCES users(id),
    CONSTRAINT friendships_user2_fk FOREIGN KEY (id2) REFERENCES users(id),
    CONSTRAINT friendships_id_order_check CHECK (id1 < id2)
);

-- DROP TABLE users;
-- DROP TABLE friendships;
