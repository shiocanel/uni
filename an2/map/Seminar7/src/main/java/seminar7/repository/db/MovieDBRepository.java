package seminar7.repository.db;

import seminar7.domain.Movie;
import seminar7.domain.validators.Validator;
import seminar7.repository.Repository;
import seminar7.repository.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MovieDBRepository implements Repository<Long,Movie> {
    private final Validator<Movie> validator;
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(Validator<Movie> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Movie> findOne(Long id) {
        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement("SELECT * FROM filme ORDER BY id");
            ResultSet rs = ps.executeQuery()) {

            while(rs.next()) {
                Movie m = new Movie(rs.getString("titlu"),
                        rs.getString("regizor"),
                        rs.getInt("an"),
                        rs.getInt("durata"));
                m.setId(rs.getLong("id"));

                if(m.getId() == id){
                    return Optional.of(m);
                }
            }
        }
        catch (SQLException e){
            throw new RepositoryException("Error while connecting to the database: " + e.getMessage(), e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Movie> findAll() {
        List<Movie> movies = new ArrayList<>();

        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement("SELECT * FROM filme ORDER BY id");
            ResultSet rs = ps.executeQuery()) {

            while(rs.next()) {
                Movie m = new Movie(rs.getString("titlu"),
                        rs.getString("regizor"),
                        rs.getInt("an"),
                        rs.getInt("durata"));
                m.setId(rs.getLong("id"));

                movies.add(m);
            }
        }
        catch (SQLException e){
            throw new RepositoryException("Error while connecting to the database: " + e.getMessage(), e);
        }

        return movies;
    }

    @Override
    public Optional<Movie> save(Movie entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity must not be null");
        }

        validator.validate(entity);
        String sql = "insert into filme(titlu, regizor, an, durata) values(?, ?, ?, ?)";

        try(Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)){

            ps.setLong(1, entity.getId());
            ps.setString(2, entity.getTitle());
            ps.setString(3, entity.getDirector());
            ps.setInt(4, entity.getDuration());
        }
        catch (SQLException e){
            throw new RepositoryException("Error while connecting to the database: " + e.getMessage(), e);
        }

        return Optional.empty();
    }

    @Override
    public Optional<Movie> delete(Long id) {
        return Optional.empty();
    }

    @Override
    public Optional<Movie> update(Movie entity) {
        return Optional.empty();
    }


    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        // TODO: Implement the logic to retrieve movies by director order by year from the database

        String sql = "SELECT * FROM filme WHERE regizor = ?";
        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement(sql);
            ResultSet rs = ps.executeQuery()) {

            while(rs.next()) {
                Movie m = new Movie(rs.getString("titlu"),
                        rs.getString("regizor"),
                        rs.getInt("an"),
                        rs.getInt("durata"));
                m.setId(rs.getLong("id"));

                movies.add(m);
                break;
            }
        }
        catch (SQLException e){
            throw new RepositoryException("Error while connecting to the database: " + e.getMessage(), e);
        }

        return movies;
    }
}
