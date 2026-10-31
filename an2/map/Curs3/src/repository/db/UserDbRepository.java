package repository.db;

import domain.User;
import domain.validators.Validator;
import repository.Repository;

public class UserDbRepository implements Repository<Long, User> {
    private Validator<User> validator;
    private String url;
    private String username;
    private String password;

    public UserDbRepository(Validator<User> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User findOne(Long aLong) {
        throw new UnsupportedOperationException("Find One not supported");
    }

    @Override
    public Iterable<User> findAll() {
        throw new UnsupportedOperationException("Find All not supported");
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("Save not supported");
    }

    @Override
    public User delete(Long aLong) {
        throw new UnsupportedOperationException("Delete not supported");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("Update not supported");
    }
}
